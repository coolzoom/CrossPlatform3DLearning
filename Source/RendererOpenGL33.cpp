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
	GLuint vertexShader = compileShader("/Game/Shaders/testShader.vert",
	GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader("/Game/Shaders/testShader.frag",
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
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void RendererOpenGL33::DrawScene(
		boost::shared_ptr<vector<WorldObject> > scene) {
	for (std::vector<WorldObject>::iterator it = scene->begin();
			it != scene->end(); it++) {

		vector<float*>* vertices = it->getModel()->getVertices();
		vector<int*>* faces = it->getModel()->getFaces();

		float positions[faces->size() * 12]; // faces * num vertices per face * 4 (3 coords + 1)

		int numFaces = faces->size();
		for (int faceIdx = 0; faceIdx != numFaces; ++faceIdx) {

			for (int verticeIdx = 0; verticeIdx != 3; ++verticeIdx) {
				for (int coordIdx = 0; coordIdx != 4; ++coordIdx) {
					if (coordIdx == 3) {
						positions[faceIdx * 4 + verticeIdx + coordIdx] = 1.0f;
					} else {
						positions[faceIdx * 4 + verticeIdx + coordIdx] =
								vertices->at(faces->at(faceIdx)[verticeIdx] - 1)[coordIdx];
					}
				}
			}
		}

		GLuint positionBufferObject;

		glGenBuffers(1, &positionBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions,
		GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
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

