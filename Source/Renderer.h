/*
 * Renderer.h
 *
 *  Created on: Jan 15, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#ifndef SDLANDOPENGL
#define SDLANDOPENGL
//#define GLEW_STATIC
#define NO_SDL_GLEXT
#include "GL/glew.h" // It seems that, when using glew,
// we do not need to include gl.h,
// glext.h or glu.h (if we do include
// them, they need to be included after
// glew.
#include "SDL_opengl.h"
#include "SDL.h"
#include "SDL_ttf.h"
#endif //SDLANDOPENGL

#include <boost/smart_ptr.hpp>
#include "WorldObject.h"
#include <vector>
#include "Configuration.h"
#include "GameLog.h"
#include <boost/smart_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace AvoidTheBug3D
{

class Renderer
{

private:

    boost::shared_ptr<Configuration> cfg;
    boost::shared_ptr<GameLog> log;

    TTF_Font *font;

    SDL_Surface *screen;

    GLuint program;

    GLuint textProgram;

    bool isOpenGL33Supported;

    bool noShaders;

    /**
     * Load a shader's source code from a file into a string
     * @param fileLocation The file's location, relative to the game path
     * @return String containing the shader's source code
     */
    string loadShaderFromFile(const string &fileLocation);

    /**
     * Compile a shader's source code
     * @param shaderSource String containing the shader's source code
     * @param shaderType Type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER - the latter for OpenGL 3.3)
     * @return OpenGL shader reference
     */
    GLuint compileShader(const string &shaderSource, const GLenum shaderType);

    /**
     * Initialise SDL
     */
    void initSDL(int width, int height, bool fullScreen);

    /**
     * Retrieve the information of what went wrong when linking a shader program
     */
    string getProgramInfoLog(const GLuint linkedProgram) const;

    /**
     * Detect if OpenGL 3.3 is supported. If not, fall back to OpenGL 2.1.
     * If neither of the two is supported, an exception is raised.
     */
    void detectOpenGLVersion();

    /**
     * Textures used in the scene, each corresponding to the name of one of
     * the rendered models
     */
    boost::unordered_map<string, GLuint> *textures;

    /**
     * Rotation transformation for rotating around the X axis
     * @param angle The angle to rotate by, in radians.
     * @return The X rotation matrix
     */
    glm::mat4x4* rotateX(const float angle) const;

    /**
     * Rotation transformation for rotating around the Y axis
     * @param angle The angle to rotate by, in radians.
	 * @return The Y rotation matrix
     */
    glm::mat4x4* rotateY(const float angle) const;

    /**
     * Rotation transformation for rotating around the Z axis
     * @param angle The angle to rotate by, in radians.
	 * @return The Z rotation matrix
     */
    glm::mat4x4* rotateZ(const float angle) const;

public:

    /**
     * Constructor
     * @param cfg The game's configuration object
     * @param log The game's logging object
     */
    Renderer(const boost::shared_ptr<Configuration> cfg,
             const boost::shared_ptr<GameLog> log);

    /**
     * Initialise renderer (OpenGL, GLEW, etc)
     * @param width The width of the window
     * @param height The height of the window
     */
    void init(const int width, const int height, const bool fullScreen);

	/**
	 * Generate a texture in OpenGL, using the given data
	 * @param name The name by which the texture will be known
	 * @param texture The texture data
	 * @param width The width of the texture, in pixels
	 * @param height The height of the texture, in pixels
	 * @return The texture handle
	 */
	GLuint generateTexture(const string &name, const float *texture, const int width, const int height);

	/**
	 * Get the handle of a texture which has already been generated (see generateTexture)
	 * @param name The name of the texture
	 * @return The texture handle (0 if not found)
	 */
	GLuint getTextureHandle(const string &name);

	/**
	 * Render a textured quad
	 */
	void renderTexturedQuad(const float *vertices, const string &textureName);

    /**
     * Draw the scene
     */
    void drawScene(
        const boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene);

    /**
     * Render some text on the screen
     */
	void renderText(const string &text, const SDL_Color &colour, 
		const float &topX, const float &topY, const float &bottomX, const float &bottomY);

    /**
     * This is a double buffered system and this commands swaps
     * the buffers
     */
    void swapBuffers();

    /**
     * Destructor
     */
    ~Renderer();
};

} /* namespace AvoidTheBug3D */

#endif /* RENDERER_H_ */
