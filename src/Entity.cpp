//
// Created by Sean on 8/5/2019.
//

#include "Entity.h"
#include "primitives/Primitive.h"

Entity::Entity(std::string ID)
{
	setID(ID);
	setPosition(position_home);
	setScale(scale_unity);
	setRotation(rotAngle_zeo, rotation_home);
}
Entity::Entity(Mesh *targetMesh, glm::vec3 startPosition, std::string ID)
{
	setID(ID);
	setMesh(targetMesh);
	setPosition(startPosition);
	setScale(scale_unity);
	setRotation(rotAngle_zeo, rotation_home);
}
void Entity::setMesh(Mesh *targetMesh)
{
	this->mesh = targetMesh;
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
	this->model = glm::mat4();
	this->model = glm::scale(this->model, this->m_scale);
	this->model = glm::rotate(this->model, this->rotAngle, this->m_rotation);
	this->model = glm::translate(this->model, this->m_position);
}

void Entity::render(Shader *targetShader)
{
	if(this->needsUpdate)
	{
		this->update();
	}
	targetShader->use();

	targetShader->setMat4("model", this->model);
	this->mesh->Draw(*targetShader);
}

void Entity::render(Shader *targetShader, unsigned int depthMap)
{
	if(this->needsUpdate)
	{
		this->update();
	}
	targetShader->use();

	targetShader->setMat4("model", this->model);
	this->mesh->Draw(*targetShader, depthMap);
}

Mesh *Entity::getMesh() const
{
	return mesh;
}
