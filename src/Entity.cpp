//
// Created by Sean on 8/5/2019.
//

#include "Entity.h"
#include "primitives/Primitive.h"

Entity::Entity()
{

	setPosition(position_home);
	setScale(scale_unity);
	setRotation(rotation_home, rotAngle_zeo);
}
Entity::Entity(Mesh *targetMesh, glm::vec3 startPosition)
{
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
	this->position = targetPosition;
	needsUpdate = true;
}
void Entity::setRotation(glm::vec3 targetRotation, float targetRotAngle)
{
	this->rotation = targetRotation;
	this->rotAngle = targetRotAngle;
	needsUpdate = true;
}
void Entity::setScale(glm::vec3 targetScale)
{
	this->scale = targetScale;
	needsUpdate = true;
}

void Entity::update()
{
	this->model = glm::mat4();
	this->model = glm::scale(this->model, this->scale);
	this->model = glm::translate(this->model, this->position);
	this->model = glm::rotate(this->model, this->rotAngle, this->rotation);
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
