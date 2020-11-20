//
// Created by Sean on 8/16/2019.
//

#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(std::string ID) : Light(ID)
{
	m_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
}

DirectionalLight::DirectionalLight(glm::vec3 direction, std::string ID) : Light(ID)
{
	m_direction = direction;
}

DirectionalLight::DirectionalLight(glm::vec3 direction,
								   glm::vec3 color,
								   std::string ID)
								   : Light(color, ID)
{
	m_direction = direction;
}

void DirectionalLight::updateDirection(glm::vec3 direction)
{
	m_direction = direction;
}

void DirectionalLight::render(Shader *targetShader)
{
	Light::render(targetShader);
	setShaderDirection(targetShader);
}

void DirectionalLight::setShaderDirection(Shader *targetShader)
{
	targetShader->setVec3(this->m_ID + ".direction", this->m_direction);
}


glm::vec3 DirectionalLight::getDirection(void)
{
	return this->m_direction;
}