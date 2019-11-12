//
// Created by Sean on 8/14/2019.
//

#include "PointLight.h"


PointLight::PointLight(std::string ID) : Light(ID)
{
	this->m_position = glm::vec3(0,0,0);

	this->m_constant = 1.0f;
	this->m_linear = 0.009;
	// Smaller is further
	this->m_quadratic = 0.000032;
}

PointLight::PointLight(glm::vec3 position, std::string ID) : Light(ID)
{
	this->m_position = position;

	this->m_constant = 1.0f;
	this->m_linear = 0.09;
	this->m_quadratic = 0.032;
}

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic, std::string ID) : Light(ID)
{
	this->m_position = position;

	this->m_constant = constant;
	this->m_linear = linear;
	this->m_quadratic = quadratic;
}

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic,
					   	glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, std::string ID) : Light(ambient, diffuse, specular, ID)
{
	this->m_position = position;

	this->m_constant = constant;
	this->m_linear = linear;
	this->m_quadratic = quadratic;
}

void PointLight::updateFalloff(float constant, float linear, float quadratic)
{
	this->m_constant = constant;
	this->m_linear = linear;
	this->m_quadratic = quadratic;
}

void PointLight::updatePosition(glm::vec3 position)
{
	this->m_position = position;
}

void PointLight::render(Shader *targetShader)
{
	// TODO: clean this up
	if(getAttachedEntity())
	{
		this->m_position = getAttachedEntity()->getPosition() + this->m_attached_entity_offset_position;
	}
	setShaderAmbient(targetShader);
	setShaderDiffuse(targetShader);
	setShaderSpecular(targetShader);
	setShaderPosition(targetShader);
	setShaderconstant(targetShader);
	setShaderLinear(targetShader);
	setShaderQuadratic(targetShader);
}

void PointLight::setShaderPosition(Shader *targetShader)
{
	targetShader->setVec3(this->m_ID + ".position", this->m_position);
}
void PointLight::setShaderconstant(Shader *targetShader)
{
	targetShader->setFloat(this->m_ID + ".constant", this->m_constant);
}
void PointLight::setShaderLinear(Shader *targetShader)
{
	targetShader->setFloat(this->m_ID + ".linear", this->m_linear);
}
void PointLight::setShaderQuadratic(Shader *targetShader)
{
	targetShader->setFloat(this->m_ID + ".quadratic", this->m_quadratic);
}

glm::vec3 PointLight::getPosition(void)
{
	return this->m_position;
}

float PointLight::getConstant(void)
{
	return this->m_constant;
}
float PointLight::getLinear(void)
{
	return this->m_linear;
}
float PointLight::getQuadratic(void)
{
	return this->m_quadratic;
}