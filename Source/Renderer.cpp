#include "Renderer.h"
#include "GameException.h"
#include <fstream>

namespace AvoidTheBug3D {

string Renderer::loadShaderFromFile(string fileLocation) {
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

GLuint Renderer::compileShader(string shaderSourceFile,
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

Renderer::Renderer(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) {
	this->cfg = cfg;
	this->log = log;
	program = 0;
}

Renderer::~Renderer() {

	LOGINFO("Renderer superclass destructor running");
}

void Renderer::Init(int width, int height) {

	//SDL_WM_SetIcon(icon, NULL);

}

} // AvoidTheBug3D

