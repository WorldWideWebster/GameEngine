//
// Created by Sean on 8/16/2019.
//

#ifndef OPENGLSETUP_DIRECTIONALLIGHT_H
#define OPENGLSETUP_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : virtual public Light
{
private:
	glm::vec3 m_direction;
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 direction);
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	void updateDirection(glm::vec3 direction);

	glm::vec3 getDirection(void);
};


#endif //OPENGLSETUP_DIRECTIONALLIGHT_H
