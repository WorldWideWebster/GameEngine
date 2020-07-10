//
// Created by Sean on 3/6/2019.
//

#include "Light.h"


Light::Light()
{
	this->m_on = true;
	this->m_color = DEFAULT_COLOR;
}

Light::Light(std::string ID)
{
	this->m_ID = ID;
	this->m_on = true;
	this->m_color = DEFAULT_COLOR;
}

Light::Light(glm::vec3 color, std::string ID)
{
    this->m_ID = ID;
    this->m_color = color;
	this->m_on = true;
}


void Light::setID(std::string ID)
{
	this->m_ID = ID;
}

void Light::render(Shader *targetShader)
{
	setShaderColor(targetShader);
	setShaderShadowCast(targetShader);
}


void Light::setShaderColor(Shader *targetShader)
{
	if (m_on)
		targetShader->setVec3(this->m_ID + ".color", this->m_color);
	else
		targetShader->setVec3(this->m_ID + ".color", glm::vec3(0));
}

void Light::setShaderShadowCast(Shader *targetShader)
{
	targetShader->setBool(this->m_ID + ".castsShadow", this->m_casts_shadow);
}

void Light::toggle(bool toggle)
{
	this->m_on = toggle;
}


glm::vec3 Light::getColor(void)
{
    return this->m_color;
}

void Light::attachToEntity(std::shared_ptr<Entity> targetEntity, glm::vec3 offset, glm::vec3 rotation)
{
	this->m_targetEntity = targetEntity;
	this->m_attached_entity_offset_position = offset;
	this->m_attached_entity_offset_rotation = rotation;
}

glm::vec3 Light::getPosition(void)
{
	return glm::vec3(0);
}
glm::vec3 Light::getDirection(void)
{
	return glm::vec3(0);
}

void Light::toggleShadowCast(bool status)
{
	this->m_casts_shadow = status;
}
