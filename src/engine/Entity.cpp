//
// Created by Sean on 8/5/2019.
//

#include "Entity.h"
#include <rendering/primitives/Primitive.h>

Entity::Entity(std::string ID)
{
	setID(ID);
	setPosition(position_home);
	setScale(scale_unity);
	setRotation(rotAngle_zeo, rotation_home);
}
Entity::Entity(Mesh *targetMesh, glm::vec3 startPosition, std::string ID) : m_model(targetMesh)
{
	setID(ID);
	setPosition(startPosition);
	setScale(scale_unity);
	setRotation(rotAngle_zeo, rotation_home);
}
Entity::Entity(Model *targetModel, glm::vec3 startPosition, std::string ID) : m_model(*targetModel)
{
	setID(ID);
	setPosition(startPosition);
	setScale(scale_unity);
	setRotation(rotAngle_zeo, rotation_home);
}
void Entity::setModel(Model *targetModel)
{
	this->m_model = *targetModel;
	needsUpdate = true;
}
void Entity::setPosition(glm::vec3 targetPosition)
{
	this->m_position = targetPosition;
	needsUpdate = true;
}

void Entity::setRotation(float targetRotAngleDeg, glm::vec3 targetRotation)
{
	this->m_rotation = targetRotation;
	this->rotAngle = glm::radians(targetRotAngleDeg);
	needsUpdate = true;
}
void Entity::setScale(glm::vec3 targetScale)
{
	this->m_scale = targetScale;
	needsUpdate = true;
}

glm::vec3 Entity::getPosition(void)
{
	return this->m_position;
}

glm::vec3 Entity::getRotation(void)
{
	return this->m_rotation;
}

glm::vec3 Entity::getScale(void)
{
	return this->m_scale;
}
void Entity::setID(std::string ID)
{
	this->m_ID = ID;
}

void Entity::update()
{
	this->m_transform = glm::mat4();
	this->m_transform = glm::scale(this->m_transform, this->m_scale);
	this->m_transform = glm::rotate(this->m_transform, this->rotAngle, this->m_rotation);
	this->m_transform = glm::translate(this->m_transform, this->m_position);
}

void Entity::render(Shader *targetShader)
{
	if(this->needsUpdate)
	{
		this->update();
	}
	targetShader->use();

	targetShader->setMat4("model", this->m_transform);
	this->m_model.Draw(*targetShader);
}

void Entity::render(Shader *targetShader, unsigned int depthMap)
{
	if(this->needsUpdate)
	{
		this->update();
	}
	targetShader->use();

	targetShader->setMat4("model", this->m_transform);
	this->m_model.Draw(*targetShader, depthMap);
}

Model Entity::getModel() const
{
	return this->m_model;
}
