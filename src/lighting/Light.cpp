//
// Created by Sean on 3/6/2019.
//

#include "Light.h"


Light::Light()
{
    this->m_ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    this->m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    this->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    this->m_ambient = ambient;
    this->m_diffuse = diffuse;
    this->m_specular = specular;
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