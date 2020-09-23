//
// Created by Sean on 8/14/2019.
//

#include "PointLight.h"


PointLight::PointLight(std::string ID) : Light(ID)
{
	this->m_position = glm::vec3(0,0,0);
	this->m_constant = 0.0000001f;
	this->m_linear = 0.000009;
	// Smaller is further
	this->m_quadratic = 0.00000032;
	calcLightRadius();
}

PointLight::PointLight(glm::vec3 position, std::string ID) : Light(ID)
{
	this->m_position = position;

	this->m_constant = 0.0000001f;
	this->m_linear = 0.000009;
	// Smaller is further
	this->m_quadratic = 0.00000032;
	calcLightRadius();
}

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic, std::string ID) : Light(ID)
{
	this->m_position = position;

	this->m_constant = constant;
	this->m_linear = linear;
	this->m_quadratic = quadratic;
	calcLightRadius();
}

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic,
					   	glm::vec3 color, std::string ID) : Light(color, ID)
{
	this->m_position = position;

	this->m_constant = constant;
	this->m_linear = linear;
	this->m_quadratic = quadratic;
	calcLightRadius();
}

void PointLight::updateFalloff(float constant, float linear, float quadratic)
{
	this->m_constant = constant;
	this->m_linear = linear;
	this->m_quadratic = quadratic;
	calcLightRadius();
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
	setShaderColor(targetShader);
	setShaderPosition(targetShader);
//	setShaderconstant(targetShader);
	setShaderLinear(targetShader);
	setShaderQuadratic(targetShader);
	setShaderRadius(targetShader);
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
void PointLight::setShaderRadius(Shader *targetShader)
{
	targetShader->setFloat(this->m_ID + ".radius", this->m_radius);
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
void PointLight::calcLightRadius(void)
{
	const float maxBrightness = std::fmaxf(std::fmaxf(this->getColor().r, this->getColor().g), this->getColor().b);
	this->m_radius = (-this->m_linear + std::sqrt(this->m_linear * this->m_linear - 4 * this->m_quadratic *
							(this->m_constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * this->m_quadratic);
}


void PointLight::setID(std::string ID)
{
	this->m_ID = this->m_lightType + "[" + ID + "]";
}
