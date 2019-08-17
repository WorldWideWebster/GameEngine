//
// Created by Sean on 8/14/2019.
//

#ifndef OPENGLSETUP_POINTLIGHT_H
#define OPENGLSETUP_POINTLIGHT_H

#include "Light.h"

class PointLight : virtual public Light
{
public:
	PointLight();
	PointLight(glm::vec3 position);
	PointLight(glm::vec3 position, float constant, float linear, float quadratic);
	PointLight(glm::vec3 position, float constant, float linear, float quadratic,
			   glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void updateFalloff(float constant, float linear, float quadratic);
	void updatePosition(glm::vec3 position);
	glm::vec3 getPosition(void);
	float getConstant(void);
	float getLinear(void);
	float getQuadratic(void);
private:
	glm::vec3 m_position;      // Position of light
	float m_constant;
	float m_linear;
	float m_quadratic;
};


#endif //OPENGLSETUP_POINTLIGHT_H
