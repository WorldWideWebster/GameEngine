//
// Created by Sean on 8/16/2019.
//

#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light()
{
	m_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
}

DirectionalLight::DirectionalLight(glm::vec3 direction) : Light()
{
	m_direction = direction;
}

DirectionalLight::DirectionalLight(glm::vec3 direction,
								   glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular)
{
	m_direction = direction;
}

void DirectionalLight::updateDirection(glm::vec3 direction)
{
	m_direction = direction;
}

glm::vec3 DirectionalLight::getDirection(void)
{
	return this->m_direction;
}