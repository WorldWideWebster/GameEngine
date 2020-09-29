//
// Created by Sean on 7/11/2019.
//
#include <memory>
#include "SkyBox.h"
#include "Primitive.h"
#include "buffer-objects/FrameBuffer.h"

SkyBox::SkyBox(Texture texture, std::shared_ptr<Camera> camera, FrameBuffer *frameBuffer)
{
	this->camera = camera;
	this->frameBuffer = frameBuffer;
}


void SkyBox::Draw(Shader shader)
{

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture.id);

	glActiveTexture(GL_TEXTURE0);


	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shader.use();
	glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
	shader.setMat4("view", view);
	shader.setMat4("projection", frameBuffer->getProjection());

	// Draw Mesh
	glDepthFunc(GL_LESS); // set depth function back to default
}