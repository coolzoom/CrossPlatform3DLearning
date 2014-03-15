/*
 * RendererOpenGL33.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: Dimitri Kourkoulis
 */

#include "RendererOpenGL33.h"
#include <fstream>
#include "GameException.h"

namespace AvoidTheBug3D {

RendererOpenGL33::RendererOpenGL33(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) :
		Renderer(cfg, log) {
	program = 0;

}

void RendererOpenGL33::Init(int width, int height) {
	Renderer::Init(width, height);

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	GLuint vertexShader = compileShader("/Game/Shaders/perspectiveMatrixShader.vert",
	GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader("/Game/Shaders/simpleShader.frag",
	GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
		string infoLogStr = infoLog;

		delete[] infoLog;
		throw GameException("Failed to link program:\n" + infoLogStr);
	} else {
		LOGINFO("Linked program successfully");

		// Perspective and offset
		glUseProgram(program);

		GLuint offsetUniform = glGetUniformLocation(program, "offset");
		glUniform3f(offsetUniform, 0.0f, 0.0f, -2.0f);

		GLuint perspectiveMatrixUniform = glGetUniformLocation(program, "perspectiveMatrix");

		float perspectiveMatrix[16];
		memset(perspectiveMatrix, 0, sizeof(float) * 16);
		perspectiveMatrix[0] = 1.0f; // frustum scale
		perspectiveMatrix[5] = 1.0f; // frustum scale
		perspectiveMatrix[10] =  (1.0f + 10.0f) / (1.0f - 10.0f) ; // (zNear + zFar) / (zNear - zFar)
		perspectiveMatrix[14] = 2.0f * 1.0f * 10.0f / (1.0f - 10.0f) ; // 2 * zNear * zFar / (zNear - zFar);
		perspectiveMatrix[11] = -1.0f; //cameraPos.z? or just the -1 factor...

		glUniformMatrix4fv(perspectiveMatrixUniform, 1, GL_FALSE, perspectiveMatrix);

		glUseProgram(0);
	}
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void RendererOpenGL33::DrawScene(
		boost::shared_ptr<vector<WorldObject> > scene) {
	for (std::vector<WorldObject>::iterator it = scene->begin();
			it != scene->end(); it++) {

		float *positions = it->getModel()->getVertexData();

		it->getModel()->outputVertexData();

		GLuint positionBufferObject;

		glGenBuffers(1, &positionBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glBufferData(GL_ARRAY_BUFFER, it->getModel()->getVertexDataSize(), positions, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) (it->getModel()->getVertexDataSize() / 2));

		glDrawArrays(GL_TRIANGLES, 0, it->getModel()->getVertexDataComponentCount());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glUseProgram(0);

		// swap buffers to display, since we're double buffered.
		SDL_GL_SwapBuffers();

	} // for std::vector<WorldObject>::iterator
}

RendererOpenGL33::~RendererOpenGL33() {
	LOGINFO("OpenGL 3.3 renderer getting destroyed");
}

string RendererOpenGL33::loadShaderFromFile(string fileLocation) {
	string shaderSource = "";
	ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			shaderSource += line + "\n";
		}
	}
	return shaderSource;
}

GLuint RendererOpenGL33::compileShader(string shaderSourceFile,
		GLenum shaderType) {

	GLuint shader = glCreateShader(shaderType);

	string shaderSource = this->loadShaderFromFile(shaderSourceFile);

	const char *shaderSourceChars = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderSourceChars, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength + 1];

		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);

		string infoLogStr = infoLog;

		delete[] infoLog;

		throw GameException(
				"Failed to compile shader:\n" + shaderSource + "\nInfo: "
						+ infoLogStr);
	} else {
		LOGINFO("Shader compiled successfully:\n" + shaderSource);
	}

	return shader;
}

} /* namespace AvoidTheBug3D */

