//
// Created by Sean on 8/16/2019.
//

#ifndef GAMEENGINE_DIRECTIONALLIGHT_H
#define GAMEENGINE_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : virtual public Light
{
private:
	glm::vec3 m_direction;
public:
	DirectionalLight(std::string ID);
	DirectionalLight(glm::vec3 direction, std::string ID);
	DirectionalLight(glm::vec3 direction, glm::vec3 color, std::string ID);

	virtual void updateDirection(glm::vec3 direction);

	void setShaderDirection(Shader *targetShader);

	virtual void render(Shader *targetShader);

	glm::vec3 getDirection(void);
};


#endif //GAMEENGINE_DIRECTIONALLIGHT_H
