#include "Renderer.h"
#include "GameException.h"
#include <fstream>
#include <boost/foreach.hpp>

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

GLuint Renderer::compileShader(string shaderSourceFile, GLenum shaderType) {

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
	textures = new boost::unordered_map<string, GLuint>();
	vertexShaderPath = "";
	fragmentShaderPath = "";
}

Renderer::~Renderer() {

	LOGINFO("Renderer superclass destructor running");
	for (boost::unordered_map<string, GLuint>::iterator it = textures->begin();
			it != textures->end(); ++it) {
		LOGINFO("Deleting texture for " + it->first);
		glDeleteTextures(1, &it->second);
	}
	delete textures;
}

void Renderer::Init(int width, int height) {

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 10.0f);

	GLuint vertexShader = compileShader(
			vertexShaderPath,
			GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath,
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

} // AvoidTheBug3D

