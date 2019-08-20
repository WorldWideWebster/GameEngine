//
// Created by Sean on 8/5/2019.
//

#ifndef OPENGLSETUP_ENTITY_H
#define OPENGLSETUP_ENTITY_H
#include "mesh.h"
#include "shader.h"


static const glm::vec3 position_home = glm::vec3(0);
static const glm::vec3 scale_unity = glm::vec3(1);
static const glm::vec3 rotation_home = glm::vec3(1);
static const float rotAngle_zeo = 0.0f;


class Entity
{
public:
	Entity();
	Entity(Mesh *targetMesh, glm::vec3 startPosition = position_home);
	void setMesh(Mesh *targetMesh);
	void setPosition(glm::vec3 targetPosition);
	void setRotation(glm::vec3 targetRotation, float targetRotAngle);
	void setScale(glm::vec3 targetScale);
	void update();
	void render(Shader *targetShader);
private:
	Mesh *mesh;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float rotAngle;
	bool needsUpdate;
	glm::mat4 model;
};


#endif //OPENGLSETUP_ENTITY_H
