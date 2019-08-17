//
// Created by Sean on 8/16/2019.
//

#include "SpotLight.h"

SpotLight::SpotLight() : DirectionalLight(), PointLight()
{
	this->m_cutOff = glm::cos(glm::radians(12.5f));
	this->m_outerCutOff = glm::cos(glm::radians(15.0f));
}

SpotLight::SpotLight(float cutOff, float outerCutOff) : DirectionalLight(), PointLight()
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}

SpotLight::SpotLight(float cutOff, float outerCutOff, glm::vec3 direction,
		  glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
		DirectionalLight(direction, ambient, diffuse, specular), PointLight()
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}


SpotLight::SpotLight(float cutOff, float outerCutOff, glm::vec3 position,
		  float constant, float linear, float quadratic,
		  glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
		DirectionalLight(), PointLight(position, constant, linear, quadratic, ambient, diffuse, specular)
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}

SpotLight::SpotLight(float cutOff, float outerCutOff, glm::vec3 position, glm::vec3 direction,
		  float constant, float linear, float quadratic,
		  glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular):
		DirectionalLight(direction, ambient, diffuse, specular),
		PointLight(position, constant, linear, quadratic, ambient, diffuse, specular)
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}


void SpotLight::setcutOff(float cutOff)
{
	this->m_cutOff = cutOff;
}
void SpotLight::setOuterCutOff(float outerCutOff)
{
	this->m_outerCutOff = outerCutOff;
}

float SpotLight::getcutOff(void)
{
	return this->m_cutOff;
}
float SpotLight::getOuterCutOff(void)
{
	return this->m_outerCutOff;
}
