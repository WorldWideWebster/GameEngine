//
// Created by Sean on 8/5/2019.
//

#ifndef GAMEENGINE_ENTITY_H
#define GAMEENGINE_ENTITY_H
#include "rendering/mesh.h"
#include "shader/shader.h"
#include <memory>


static const glm::vec3 position_home = glm::vec3(0);
static const glm::vec3 scale_unity = glm::vec3(1);
static const glm::vec3 rotation_home = glm::vec3(1);	// Why does this have to be 1? (things don't render otherwise)
static const float rotAngle_zeo = 0.0f;

static int EntityNum = 0;

class Entity
{
public:
	Entity(std::string ID = "entity_" + std::to_string(EntityNum++));
	Entity(Mesh *targetMesh, glm::vec3 startPosition = position_home, std::string ID = "entity_" + std::to_string(EntityNum++));
	void setMesh(Mesh *targetMesh);
	Mesh *getMesh() const;

	void setPosition(glm::vec3 targetPosition);

	/**
	 * @brief Sets rotation of an Entity
	 * @param targetRotAngleDeg - Rotation angle in degrees
	 * @param targetRotation  - Rotation vector mask (put 1 in axis to rotate about)
	 */
	void setRotation(float targetRotAngleDeg, glm::vec3 targetRotation);
	void setScale(glm::vec3 targetScale);
	void setID(std::string ID);
	glm::vec3 getPosition(void);
	glm::vec3 getRotation(void);
	glm::vec3 getScale(void);

	void update();
	virtual void render(Shader *targetShader);
	void render(Shader *targetShader, unsigned int depthMap);

	std::string m_ID;

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	float rotAngle;
	bool needsUpdate;
	glm::mat4 model;
	Mesh *mesh;

};


#endif //GAMEENGINE_ENTITY_H
