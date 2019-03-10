//
// Created by Sean on 3/6/2019.
//

#include "Light.h"


Light::Light()
{
    this->type = POINT_LIGHT;
    this->position = glm::vec3(0,0,0);
    this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    this->specular = glm::vec3(1.0f, 1.0f, 1.0f);

    this->constant = 1.0f;
    this->linear = 0.09;
    this->quadratic = 0.032;
}

Light::Light(glm::vec3 pos)
{
    this->type = POINT_LIGHT;
    this->position = pos;
    this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    this->specular = glm::vec3(1.0f, 1.0f, 1.0f);

    this->constant = 1.0f;
    this->linear = 0.09;
    this->quadratic = 0.032;
}

Light::Light(short type)
{
    this->type = type;

    switch(type)
    {
        case AMBIENT_LIGHT:
            break;
        case DIRECTIONAL_LIGHT:
            this->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
            this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
            this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
            this->specular = glm::vec3(1.0f, 1.0f, 1.0f);
            break;
        case POINT_LIGHT:
            this->position = glm::vec3(0,0,0);
            this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
            this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
            this->specular = glm::vec3(1.0f, 1.0f, 1.0f);

            this->constant = 1.0f;
            this->linear = 0.09;
            this->quadratic = 0.032;
            break;
        case SPOT_LIGHT:
            this->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
            this->position = glm::vec3(0,0,0);
            this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
            this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
            this->specular = glm::vec3(1.0f, 1.0f, 1.0f);

            this->constant = 1.0f;
            this->linear = 0.09;
            this->quadratic = 0.032;

            this->cutOff = glm::cos(glm::radians(12.5f));
            this->outerCutOff = glm::cos(glm::radians(15.0f));
            break;
        default:
            break;
    }
}




void Light::setType(short type)
{
    this->type = type;
}

void Light::setPosition(glm::vec3 position)
{
    this->position = position;
}
void Light::setDirection(glm::vec3 direction)
{
    this->direction = direction;
}
void Light::setcutOff(float cutOff)
{
    this->cutOff = cutOff;
}
void Light::setOuterCutOff(float outerCutOff)
{
    this->outerCutOff = outerCutOff;
}

void Light::setAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}
void Light::setDiffuse(glm::vec3 diffuse)
{
    this->diffuse = diffuse;
}
void Light::setSpecular(glm::vec3 specular)
{
    this->specular = specular;
}

void Light::setConstant(float constant)
{
    this->constant = constant;
}
void Light::setLinear(float linear)
{
    this->linear = linear;
}
void Light::setQuadratic(float quadratic)
{
    this->quadratic = quadratic;
}



glm::vec3 Light::getPosition(void)
{
    return this->position;
}
glm::vec3 Light::getDirection(void)
{
    return this->direction;
}
float Light::getcutOff(void)
{
    return this->cutOff;
}
float Light::getOuterCutOff(void)
{
    return this->outerCutOff;
}

glm::vec3 Light::getAmbient(void)
{
    return this->ambient;
}
glm::vec3 Light::getDiffuse(void)
{
    return this->diffuse;
}
glm::vec3 Light::getSpecular(void)
{
    return this->specular;
}

float Light::getConstant(void)
{
    return this->constant;
}
float Light::getLinear(void)
{
    return this->linear;
}
float Light::getQuadratic(void)
{
    return this->quadratic;
}

short Light::getType(void)
{
    return this->type;
}
