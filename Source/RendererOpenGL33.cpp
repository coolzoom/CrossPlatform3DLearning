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

}

void RendererOpenGL33::Init(int width, int height) {
	Renderer::Init(width, height);
	compileShader("/Game/Shaders/testShader.vert", GL_VERTEX_SHADER);
}

void RendererOpenGL33::DrawScene(
		boost::shared_ptr<vector<WorldObject> > scene) {
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

GLuint RendererOpenGL33::compileShader(string shaderSourceFile, GLenum shaderType) {

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

		delete infoLog;

		throw GameException(
				"Failed to compile shader:\n" + shaderSource + "\nInfo: "
						+ infoLogStr);
	} else {
		LOGINFO("Shader compiled successfully:\n" + shaderSource);
	}

	return shader;
}

GLuint RendererOpenGL33::getProgram() {
	return 0;
}

} /* namespace AvoidTheBug3D */

