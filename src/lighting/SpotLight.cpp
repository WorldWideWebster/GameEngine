//
// Created by Sean on 8/16/2019.
//

#include "SpotLight.h"

SpotLight::SpotLight(std::string ID) : Light(ID), DirectionalLight(ID), PointLight(ID)
{
	this->m_cutOff = glm::cos(glm::radians(32.5f));
	this->m_outerCutOff = glm::cos(glm::radians(45.0f));
}

SpotLight::SpotLight(float cutOff, float outerCutOff, std::string ID) : Light(ID), DirectionalLight(ID), PointLight(ID)
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}

SpotLight::SpotLight(float cutOff, float outerCutOff, glm::vec3 direction,
		  glm::vec3 color, std::string ID) :
		Light(ID), DirectionalLight(direction, color, ID), PointLight(ID)
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}


SpotLight::SpotLight(float cutOff, float outerCutOff, glm::vec3 position,
		  float constant, float linear, float quadratic,
		  glm::vec3 color, std::string ID) :
		Light(ID), DirectionalLight(ID), PointLight(position, constant, linear, quadratic, color, ID)
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}

SpotLight::SpotLight(float cutOff, float outerCutOff, glm::vec3 position, glm::vec3 direction,
		  float constant, float linear, float quadratic,
		  glm::vec3 color, std::string ID):
		Light(ID), DirectionalLight(direction, color, ID),
		PointLight(position, constant, linear, quadratic, color, ID)
{
	this->m_cutOff = cutOff;
	this->m_outerCutOff = outerCutOff;
}

void SpotLight::render(Shader *targetShader)
{
	DirectionalLight::render(targetShader);
	PointLight::render(targetShader);
	targetShader->setFloat("spotLights[0].cutOff", this->m_cutOff);
	targetShader->setFloat("spotLights[0].outerCutOff", this->m_outerCutOff);
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
