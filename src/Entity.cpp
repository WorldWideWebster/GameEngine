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
	setRotation(rotation_home, rotAngle_zeo);
}
Entity::Entity(Mesh *targetMesh, glm::vec3 startPosition, std::string ID)
{
	setID(ID);
	setMesh(targetMesh);
	setPosition(startPosition);
	setScale(scale_unity);
	setRotation(rotation_home, rotAngle_zeo);
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
void Entity::setRotation(glm::vec3 targetRotation, float targetRotAngle)
{
	this->m_rotation = targetRotation;
	this->rotAngle = targetRotAngle;
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
void Entity::setID(std::string ID)
{
	this->m_ID = ID;
}


void Entity::update()
{
	this->model = glm::mat4();
	this->model = glm::scale(this->model, this->m_scale);
	this->model = glm::translate(this->model, this->m_position);
	this->model = glm::rotate(this->model, this->rotAngle, this->m_rotation);
}

static bool once = false;

void Entity::render(Shader *targetShader)
{
	if(needsUpdate)
	{
		this->update();
	}
	targetShader->use();

	targetShader->setMat4("model", model);
	mesh->Draw(*targetShader);
}
