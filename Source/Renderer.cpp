#include "Renderer.h"
#include "GameException.h"
#include <fstream>
#include <boost/foreach.hpp>
#include <glm/glm.hpp>
#include <boost/unordered_map.hpp>

using namespace boost;

namespace AvoidTheBug3D
{

string Renderer::loadShaderFromFile(string fileLocation)
{
    string shaderSource = "";
    ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            shaderSource += line + "\n";
        }
    }
    return shaderSource;
}

GLuint Renderer::compileShader(string shaderSourceFile, GLenum shaderType)
{

    GLuint shader = glCreateShader(shaderType);

    string shaderSource = this->loadShaderFromFile(shaderSourceFile);

    const char *shaderSourceChars = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderSourceChars, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength + 1];

        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);

        string infoLogStr = infoLog;

        delete[] infoLog;

        throw GameException(
            "Failed to compile shader:\n" + shaderSource + "\nInfo: "
            + infoLogStr);
    }
    else
    {
        LOGINFO("Shader " + shaderSourceFile + " compiled successfully.");
    }

    return shader;
}

Renderer::Renderer(boost::shared_ptr<Configuration> cfg,
                   boost::shared_ptr<GameLog> log)
{
    this->cfg = cfg;
    this->log = log;
    isOpenGL33Supported = false;

    program = 0;
    textures = new boost::unordered_map<string, GLuint>();
    vertexShaderPath = "";
    fragmentShaderPath = "";

    xRotationMatrix = boost::shared_ptr<float>(new float[16]);
    yRotationMatrix = boost::shared_ptr<float>(new float[16]);
    zRotationMatrix = boost::shared_ptr<float>(new float[16]);

    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;
}

Renderer::~Renderer()
{

    LOGINFO("Renderer superclass destructor running");
    for (boost::unordered_map<string, GLuint>::iterator it = textures->begin();
            it != textures->end(); ++it)
    {
        LOGINFO("Deleting texture for " + it->first);
        glDeleteTextures(1, &it->second);
    }
    delete textures;

    SDL_FreeSurface(icon);
    SDL_FreeSurface(screen);
    SDL_Quit();
}

void Renderer::initSDL(int width, int height)
{
    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOGERROR(SDL_GetError());
        throw GameException(string("Unable to initialise SDL"));
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_WM_SetCaption("SDL Application", "SDL Test");

    icon = SDL_LoadBMP("ONLINE32.BMP");
    SDL_WM_SetIcon(icon, NULL);
    screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL); // *** SDL_HWSURFACE //DL_OPENGL |SDL_FULLSCREEN SDL_HWSURFACE SDL_DOUBLEBUF | );

    if (!screen)
    {

        LOGERROR(SDL_GetError());
        throw GameException("Unable to set video");
    }
}

void Renderer::detectOpenGLVersion()
{
    if (glewInit() != GLEW_OK)
    {
        throw GameException("Error initialising GLEW");
    }
    else
    {
        string glewVersion = (char*) glewGetString(GLEW_VERSION);
        LOGINFO("Using GLEW version " + glewVersion);
    }

    string glVersion = (char*) glGetString(GL_VERSION);
    glVersion = "OpenGL version supported by machine: " + glVersion;
    LOGINFO(glVersion);

    if (glewIsSupported("GL_VERSION_3_3"))
    {
        LOGINFO("Ready for OpenGL 3.3");
        isOpenGL33Supported = true;
    }
    else if (glewIsSupported("GL_VERSION_2_1"))
    {
        LOGINFO("Ready for OpenGL 2.1");
    }
    else
    {
        throw GameException(
            "None of the supported OpenGL versions (3.3 nor 2.1) are available.");
    }

}

void Renderer::init(int width, int height)
{

    this->initSDL(width, height);

    this->detectOpenGLVersion();

    if (isOpenGL33Supported)
    {
        vertexShaderPath = "/Game/Shaders/OpenGL33/perspectiveMatrixLightedShader.vert";
        fragmentShaderPath = "/Game/Shaders/OpenGL33/textureShader.frag";

    }
    else
    {
        vertexShaderPath =
            "/Game/Shaders/OpenGL21/perspectiveMatrixLightedShader.vert";
        fragmentShaderPath = "/Game/Shaders/OpenGL21/textureShader.frag";
    }

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 10.0f);

    GLuint vertexShader = compileShader(vertexShaderPath,
                                        GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderPath,
                                          GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
        string infoLogStr = infoLog;

        delete[] infoLog;
        throw GameException("Failed to link program:\n" + infoLogStr);
    }
    else
    {
        LOGINFO("Linked program successfully");

        // Perspective and offset
        glUseProgram(program);

        GLuint offsetUniform = glGetUniformLocation(program, "offset");
        glUniform3f(offsetUniform, 0.0f, -1.0f, -4.0f);

        GLuint perspectiveMatrixUniform = glGetUniformLocation(program,
                                          "perspectiveMatrix");

        float perspectiveMatrix[16];
        memset(perspectiveMatrix, 0, sizeof(float) * 16);
        perspectiveMatrix[0] = 1.0f; // frustum scale
        perspectiveMatrix[5] = 1.0f; // frustum scale
        perspectiveMatrix[10] = (1.0f + 10.0f) / (1.0f - 10.0f); // (zNear + zFar) / (zNear - zFar)
        perspectiveMatrix[14] = 2.0f * 1.0f * 10.0f / (1.0f - 10.0f); // 2 * zNear * zFar / (zNear - zFar);
        perspectiveMatrix[11] = -1.0f; //cameraPos.z? or just the -1 factor...

        glUniformMatrix4fv(perspectiveMatrixUniform, 1, GL_FALSE,
                           perspectiveMatrix);

        glUseProgram(0);
    }
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(10.0f);
}

void Renderer::drawScene(boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene)
{

// Clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the shaders prepared at initialisation
    glUseProgram(program);

    // Rotate everything, just a bit. This will be removed later,
    // once rendering has been finalised but, for now, it helps
    // test things.
    if (xAngle > 6.28)
        xAngle = 0.0;
    xAngle += 0.03f;

    if (yAngle > 6.28)
        yAngle = 0.0;
    yAngle += 0.03f;

    /*if (zAngle > 6.28)
    		zAngle = 0.0;
    	zAngle += 0.03;*/

    GLuint xRotationMatrixUniform = glGetUniformLocation(program,
                                    "xRotationMatrix");
    GLuint yRotationMatrixUniform = glGetUniformLocation(program,
                                    "yRotationMatrix");
    GLuint zRotationMatrixUniform = glGetUniformLocation(program,
                                    "zRotationMatrix");

    constructXRotationMatrix(xAngle);
    constructYRotationMatrix(yAngle);
    constructZRotationMatrix(zAngle);

    glUniformMatrix4fv(xRotationMatrixUniform, 1, GL_TRUE,
                       xRotationMatrix.get());
    glUniformMatrix4fv(yRotationMatrixUniform, 1, GL_TRUE,
                       yRotationMatrix.get());
    glUniformMatrix4fv(zRotationMatrixUniform, 1, GL_TRUE,
                       zRotationMatrix.get());

    // Pick up each model in the "world" and render it.
    for (std::vector<boost::shared_ptr<WorldObject> >::iterator it =
                scene->begin(); it != scene->end(); it++)
    {

        GLuint vao = 0;
        if (isOpenGL33Supported)
        {
            // Generate VAO
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
        }

        GLuint positionBufferObject = 0;
        GLuint indexBufferObject = 0;
        GLuint normalsBufferObject = 0;
        GLuint sampler = 0;
        GLuint texture = 0;
        GLuint uvBufferObject = 0;

        // Pass the vertex positions to the shaders
        glGenBuffers(1, &positionBufferObject);

        glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
        glBufferData(GL_ARRAY_BUFFER,
                     it->get()->getModel()->getVertexDataSize(),
                     it->get()->getModel()->getVertexData(),
                     GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

        // Pass vertex indexes

        glGenBuffers(1, &indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     it->get()->getModel()->getIndexDataSize(),
                     it->get()->getModel()->getIndexData(),
                     GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);


        // Index attribute array
        glEnableVertexAttribArray(1);


        // Lighting

        glm::vec3 lightDirection(-0.9f, -0.9f, 0.9f);
        GLuint lightDirectionUniform = glGetUniformLocation(program,
                                       "lightDirection");
        glUniform3fv(lightDirectionUniform, 1,
                     glm::value_ptr(lightDirection));

        glGenBuffers(1, &normalsBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
        glBufferData(GL_ARRAY_BUFFER,
                     it->get()->getModel()->getNormalsDataSize(),
                     it->get()->getModel()->getNormalsData(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Add texture if that is contained in the model
        boost::shared_ptr<Image> textureObj = it->get()->getTexture();

        if (textureObj)
        {

            /*glActiveTexture(GL_TEXTURE0);*/

            unordered_map<string, GLuint>::iterator nameTexturePair = textures->find(it->get()->getName());

            // Textures are heavy to be moving back and forth so only create them once per model
            if(nameTexturePair != textures->end())
            {
                texture = nameTexturePair->second;
                glBindTexture(GL_TEXTURE_2D, texture);
            }
            else
            {
                glGenTextures(1, &texture);

                glBindTexture(GL_TEXTURE_2D, texture);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

                GLint internalFormat = isOpenGL33Supported ? GL_RGBA32F : GL_RGBA;

                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, textureObj->getWidth(), textureObj->getHeight(), 0, GL_RGBA,
                             GL_FLOAT, textureObj->getData());

                textures->insert(make_pair(it->get()->getName(), texture));
            }

            // UV Coordinates

            glGenBuffers(1, &uvBufferObject);
            glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);
            glBufferData(GL_ARRAY_BUFFER,
                         it->get()->getModel()->getTextureCoordsDataSize(),
                         it->get()->getModel()->getTextureCoordsData(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        }

        // Throw an exception if there was an error in OpenGL, during
        // any of the above.
        GLenum errorCode = glGetError();
        if (errorCode != GL_NO_ERROR)
        {
            throw GameException(string((char*)gluErrorString(errorCode)));
        }

        // Draw
        glDrawElements(GL_TRIANGLES,
                       it->get()->getModel()->getIndexDataIndexCount(),
                       GL_UNSIGNED_INT, 0);

        // Clear stuff
        if (textureObj)
        {
            glDisableVertexAttribArray(2);
        }

        if (positionBufferObject != 0)
        {
            glDeleteBuffers(1, &positionBufferObject);
        }

        if ( indexBufferObject != 0)
        {
            glDeleteBuffers(1, &indexBufferObject);
        }
        if ( normalsBufferObject != 0)
        {
            glDeleteBuffers(1, &normalsBufferObject);
        }
        if ( sampler != 0)
        {
            glDeleteSamplers(1, &sampler);
        }
        if ( uvBufferObject != 0)
        {
            glDeleteBuffers(1, &uvBufferObject);
        }

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

        if (isOpenGL33Supported)
        {
            glDeleteVertexArrays(1, &vao);
            glBindVertexArray(0);
        }
        glUseProgram(0);

        // Swap buffers to display, since we're double buffered.
        SDL_GL_SwapBuffers();

    } // for std::vector<WorldObject>::iterator

}

void Renderer::constructXRotationMatrix(float angle)
{
    xRotationMatrix.get()[0] = 1;
    xRotationMatrix.get()[1] = 0;
    xRotationMatrix.get()[2] = 0;
    xRotationMatrix.get()[3] = 0;

    xRotationMatrix.get()[4] = 0;
    xRotationMatrix.get()[5] = glm::cos(angle);
    xRotationMatrix.get()[6] = -glm::sin(angle);
    xRotationMatrix.get()[7] = 0;

    xRotationMatrix.get()[8] = 0;
    xRotationMatrix.get()[9] = glm::sin(angle);
    xRotationMatrix.get()[10] = glm::cos(angle);
    xRotationMatrix.get()[11] = 0;

    xRotationMatrix.get()[12] = 0;
    xRotationMatrix.get()[13] = 0;
    xRotationMatrix.get()[14] = 0;
    xRotationMatrix.get()[15] = 1.0f;
}

void Renderer::constructYRotationMatrix(float angle)
{
    yRotationMatrix.get()[0] = glm::cos(angle);
    yRotationMatrix.get()[1] = 0;
    yRotationMatrix.get()[2] = glm::sin(angle);
    yRotationMatrix.get()[3] = 0;

    yRotationMatrix.get()[4] = 0;
    yRotationMatrix.get()[5] = 1;
    yRotationMatrix.get()[6] = 0;
    yRotationMatrix.get()[7] = 0;

    yRotationMatrix.get()[8] = -glm::sin(angle);
    yRotationMatrix.get()[9] = 0;
    yRotationMatrix.get()[10] = glm::cos(angle);
    yRotationMatrix.get()[11] = 0;

    yRotationMatrix.get()[12] = 0;
    yRotationMatrix.get()[13] = 0;
    yRotationMatrix.get()[14] = 0;
    yRotationMatrix.get()[15] = 1.0f;
}

void Renderer::constructZRotationMatrix(float angle)
{
    zRotationMatrix.get()[0] = glm::cos(angle);
    zRotationMatrix.get()[1] = -glm::sin(angle);
    zRotationMatrix.get()[2] = 0;
    zRotationMatrix.get()[3] = 0;

    zRotationMatrix.get()[4] = glm::sin(angle);
    zRotationMatrix.get()[5] = glm::cos(angle);
    zRotationMatrix.get()[6] = 0;
    zRotationMatrix.get()[7] = 0;

    zRotationMatrix.get()[8] = 0;
    zRotationMatrix.get()[9] = 0;
    zRotationMatrix.get()[10] = 1.0f;
    zRotationMatrix.get()[11] = 0;

    zRotationMatrix.get()[12] = 0;
    zRotationMatrix.get()[13] = 0;
    zRotationMatrix.get()[14] = 0;
    zRotationMatrix.get()[15] = 1.0f;
}

} // AvoidTheBug3D

