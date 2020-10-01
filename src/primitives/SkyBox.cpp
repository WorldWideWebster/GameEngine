//
// Created by Sean on 7/11/2019.
//
#include <memory>
#include "SkyBox.h"
#include "Primitive.h"
#include "buffer-objects/FrameBuffer.h"

SkyBox::SkyBox(Texture texture, std::shared_ptr<Camera> camera, glm::mat4 m_projection, Shader shader)
{
	this->m_texture = texture;
	this->camera = camera;
	this->m_projection = m_projection;
	this->setMesh(new Mesh(new Cube, texture));
	this->m_shader = shader;
}


void SkyBox::render(void)
{

	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	this->m_shader.use();
	glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
	this->m_shader.setMat4("view", view);
	this->m_shader.setMat4("projection", m_projection);

	// Draw Mesh
	this->getMesh()->DrawCubeMap(this->m_shader);
	glDepthFunc(GL_LESS); // set depth function back to default
}

void SkyBox::setShader(const Shader &shader)
{
	m_shader = shader;
}
