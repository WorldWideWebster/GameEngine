//
// Created by Sean on 8/16/2019.
//

#ifndef OPENGLSETUP_SPOTLIGHT_H
#define OPENGLSETUP_SPOTLIGHT_H

#include "DirectionalLight.h"
#include "PointLight.h"

class SpotLight : public DirectionalLight, public PointLight
{
private:
	float m_cutOff;
	float m_outerCutOff;
private:
	SpotLight(std::string ID);
	SpotLight(float cutOff, float outerCutOff, std::string ID);
	SpotLight(float cutOff, float outerCutOff, glm::vec3 direction,
			   glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, std::string ID);
	SpotLight(float cutOff, float outerCutOff, glm::vec3 position,
			  float constant, float linear, float quadratic,
			  glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, std::string ID);
	SpotLight(float cutOff, float outerCutOff, glm::vec3 position, glm::vec3 direction,
			  float constant, float linear, float quadratic,
			  glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, std::string ID);

	void setcutOff(float cutOff);
	void setOuterCutOff(float outerCutOff);

	void render(Shader *targetShader);

	float getcutOff(void);
	float getOuterCutOff(void);


};


#endif //OPENGLSETUP_SPOTLIGHT_H
