/*
* RendererOpenGL33.cpp
*
*  Created on: Jan 19, 2014
*      Author: Dimitri Kourkoulis
*/

#include "RendererOpenGL33.h"
#include "GameException.h"

namespace AvoidTheBug3D {

	RendererOpenGL33::RendererOpenGL33(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) :
	Renderer(cfg, log) {

		xRotationMatrix = boost::shared_ptr<float>(new float[16]);
		yRotationMatrix = boost::shared_ptr<float>(new float[16]);
		zRotationMatrix = boost::shared_ptr<float>(new float[16]);

		xAngle = 0.0f;
		yAngle = 0.0f;
		zAngle = 0.0f;

		vertexShaderPath = "/Game/Shaders/OpenGL33/perspectiveMatrixLightedShader.vert";
		fragmentShaderPath = "/Game/Shaders/OpenGL33/textureShader.frag";

	}

	void RendererOpenGL33::Init(int width, int height) {
		Renderer::Init(width, height);

	}

	void RendererOpenGL33::DrawScene(
		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene) {

			if (xAngle > 6.28)
				xAngle = 0.0;
			xAngle += 0.03f;

			if (yAngle > 6.28)
				yAngle = 0.0;
			yAngle += 0.03f;

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


						glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
						glBindBuffer(GL_ARRAY_BUFFER, 0);
					}

					boost::shared_ptr<Image> textureObj = it->get()->getTexture();
					GLuint sampler;
					if (textureObj) {
						GLuint texture;
						if (textures->find(it->get()->getName()) == textures->end())
						{
							glGenTextures(1, &texture);
							glBindTexture(GL_TEXTURE_2D, texture);

							glTexStorage2D(GL_TEXTURE_2D, 0, GL_RED, 3 * textureObj->getWidth(),
								3 * textureObj->getHeight());
							glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 3 * textureObj->getWidth(),
								3 * textureObj->getHeight(), GL_RED, GL_UNSIGNED_SHORT,
								(GLvoid *)textureObj->getData());
							/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);*/

							/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
*/
							glBindTexture(GL_TEXTURE_2D, 0);
							textures->insert(boost::unordered_map<string, GLuint>::value_type(it->get()->getName(), texture));
						}
						else
						{
							texture = textures->find(it->get()->getName())->second;
						}


						glGenSamplers(1, &sampler);
						glBindSampler(texture, sampler);

						GLuint textureUniformLoc = glGetUniformLocation(program, "textureImage");
						glUniform1i(textureUniformLoc, sampler);

						GLuint uvBufferObject;
						glGenBuffers(1, &uvBufferObject);
						glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);
						glBufferData(GL_ARRAY_BUFFER,
							it->get()->getModel()->getTextureCoordsDataSize(),
							it->get()->getModel()->getTextureCoordsData(), GL_STATIC_DRAW);
						glEnableVertexAttribArray(2);
						glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
						glBindBuffer(GL_ARRAY_BUFFER, 0);
					}

					if (it->get()->getModel()->isIndexedDrawing()) {
						glDrawElements(GL_TRIANGLES,
							it->get()->getModel()->getIndexDataIndexCount(),
							GL_UNSIGNED_INT, 0);
					} else {
						glDrawArrays(GL_TRIANGLES, 0,
							it->get()->getModel()->getVertexDataComponentCount());
					}
					if (textureObj) {
						glDisableVertexAttribArray(2);
						glDeleteSamplers(1, &sampler);
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

} /* namespace AvoidTheBug3D */

