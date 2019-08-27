//
// Created by Sean on 3/6/2019.
//

#include "Light.h"


Light::Light(std::string ID)
{
    this->m_ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    this->m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    this->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_ID = ID;
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, std::string ID)
{
    this->m_ambient = ambient;
    this->m_diffuse = diffuse;
    this->m_specular = specular;
    this->m_ID = ID;
}

void Light::setAmbient(glm::vec3 ambient)
{
    this->m_ambient = ambient;
}
void Light::setDiffuse(glm::vec3 diffuse)
{
    this->m_diffuse = diffuse;
}
void Light::setSpecular(glm::vec3 specular)
{
    this->m_specular = specular;
}

void Light::render(Shader *targetShader)
{
	/*
	setShaderAmbient(targetShader);
	setShaderDiffuse(targetShader);
	setShaderSpecular(targetShader);
	 */
	targetShader->setVec3("dirLights[0].ambient", this->m_ambient);
	targetShader->setVec3("dirLights[0].diffuse", this->m_diffuse);
	targetShader->setVec3("dirLights[0].specular", this->m_specular);
}

void Light::setShaderAmbient(Shader *targetShader)
{
	std::cout << this->m_ID + ".ambient" << ": "<< this->m_ambient.x <<  std::endl;
	targetShader->setVec3(this->m_ID + ".ambient", this->m_ambient);
}
void Light::setShaderDiffuse(Shader *targetShader)
{
	std::cout << this->m_ID + ".diffuse" << ": "<< this->m_diffuse.x <<  std::endl;
	targetShader->setVec3(this->m_ID + ".diffuse", this->m_diffuse);
}
void Light::setShaderSpecular(Shader *targetShader)
{
	std::cout << this->m_ID + ".specular" << ": "<< this->m_specular.x <<  std::endl;
	targetShader->setVec3(this->m_ID + ".specular", this->m_specular);
}

glm::vec3 Light::getAmbient(void)
{
    return this->m_ambient;
}
glm::vec3 Light::getDiffuse(void)
{
    return this->m_diffuse;
}
glm::vec3 Light::getSpecular(void)
{
    return this->m_specular;
}