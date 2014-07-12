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

	xRotationMatrix = boost::shared_ptr<float>(new float[16]);
	yRotationMatrix = boost::shared_ptr<float>(new float[16]);
	zRotationMatrix = boost::shared_ptr<float>(new float[16]);

	xAngle = 0.0f;
	yAngle = 0.0f;
	zAngle = 0.0f;

}

void RendererOpenGL33::Init(int width, int height) {
	Renderer::Init(width, height);

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 10.0f);

	GLuint vertexShader = compileShader(
			"/Game/Shaders/perspectiveMatrixLightedShader.vert",
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

void RendererOpenGL33::DrawScene(
		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene) {

	if (xAngle > 6.28)
		xAngle = 0.0;
	xAngle += 0.03;

	if (yAngle > 6.28)
		yAngle = 0.0;
	yAngle += 0.03;

//	if (zAngle > 6.28)
//			zAngle = 0.0;
//		zAngle += 0.03;

	for (std::vector<boost::shared_ptr<WorldObject> >::iterator it =
			scene->begin(); it != scene->end(); it++) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);

		GLuint multiColourBoolUniform = glGetUniformLocation(program,
				"multiColourBool");
		glUniform1ui(multiColourBoolUniform,
				(it->get()->getModel()->isMultiColour() ? 1 : 0));

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

		// Generate VAO
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint positionBufferObject;
		glGenBuffers(1, &positionBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glBufferData(GL_ARRAY_BUFFER,
				it->get()->getModel()->getVertexDataSize(),
				it->get()->getModel()->getVertexData(),
				GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		if (it->get()->getModel()->isIndexedDrawing()) {
			GLuint indexBufferObject;
			glGenBuffers(1, &indexBufferObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					it->get()->getModel()->getIndexDataSize(),
					it->get()->getModel()->getIndexData(),
					GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
		}

		boost::shared_ptr<Image> textureObj = it->get()->getTexture();

		if (textureObj) {
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureObj->getWidth(),
					textureObj->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
					textureObj->getData());

			glActiveTexture(GL_TEXTURE0);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
//
//			glGenerateMipmap(GL_TEXTURE_2D);
			//glBindTexture(GL_TEXTURE_2D, 0);


		}

		glEnableVertexAttribArray(1);

		if (it->get()->getModel()->isMultiColour()) {
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
					(void*) (it->get()->getModel()->getVertexDataSize() / 2));
		} else {
			glm::vec3 lightDirection(0.6f, -0.5f, -0.2f);
			GLuint lightDirectionUniform = glGetUniformLocation(program,
					"lightDirection");
			glUniformMatrix3fv(lightDirectionUniform, 1, GL_TRUE,
					glm::value_ptr(lightDirection));

			GLuint normalsBufferObject;
			glGenBuffers(1, &normalsBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
			glBufferData(GL_ARRAY_BUFFER,
					it->get()->getModel()->getNormalsDataSize(),
					it->get()->getModel()->getNormalsData(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		}

		if (it->get()->getModel()->isIndexedDrawing()) {
			glDrawElements(GL_TRIANGLES,
					it->get()->getModel()->getIndexDataIndexCount(),
					GL_UNSIGNED_INT, 0);
		} else {
			glDrawArrays(GL_TRIANGLES, 0,
					it->get()->getModel()->getVertexDataComponentCount());
		}

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		glUseProgram(0);

		// swap buffers to display, since we're double buffered.
		SDL_GL_SwapBuffers();

	} // for std::vector<WorldObject>::iterator
}

void RendererOpenGL33::constructXRotationMatrix(float angle) {
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

void RendererOpenGL33::constructYRotationMatrix(float angle) {
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

void RendererOpenGL33::constructZRotationMatrix(float angle) {
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

