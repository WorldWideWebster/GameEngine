//
// Created by Sean on 4/14/2019.
//
#include "Lighting.h"
#include <GLFW/glfw3.h>

void doLighting(Shader *shader, Camera camera, glm::vec3 lightPos, bool flashlight)
{
    glm::vec3 lightDir = glm::vec3(2 * cos(glfwGetTime()), 0, 2 * sin(glfwGetTime()));

    //lightDir = glm::vec3(2 * cos(glfwGetTime()), 0, 2 * sin(glfwGetTime()));

    // be sure to activate shader when setting uniforms/drawing objects
    shader->use();
    shader->setVec3("viewPos", camera.Position);
    shader->setFloat("material.shininess", 32.0f);
    shader->setInt("num_point_lights", 1);
    shader->setInt("num_dir_lights", 1);
    shader->setInt("num_spot_lights", 1);
    // directional light
    shader->setVec3("dirLights[0].direction", -1.0f, -1.0f, -0.3f);
    shader->setVec3("dirLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shader->setVec3("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f);
    shader->setVec3("dirLights[0].specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    shader->setVec3("pointLights[0].position", lightPos);
    shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    shader->setFloat("pointLights[0].constant", 1.0f);
    shader->setFloat("pointLights[0].linear", 0.09);
    shader->setFloat("pointLights[0].quadratic", 0.032);
    if(flashlight)
    {
        // spotLight
        shader->setVec3("spotLights[0].position", camera.Position);
        shader->setVec3("spotLights[0].direction", camera.Front);
        shader->setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
        shader->setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
        shader->setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
        shader->setFloat("spotLights[0].constant", 1.0f);
        shader->setFloat("spotLights[0].linear", 0.09);
        shader->setFloat("spotLights[0].quadratic", 0.032);
        shader->setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
        shader->setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));
    }
    else
    {
        shader->setVec3("spotLights[0].position", camera.Position);
        shader->setVec3("spotLights[0].direction", camera.Front);
        shader->setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
        shader->setVec3("spotLights[0].diffuse", 0.0f, 0.0f, 0.0f);
        shader->setVec3("spotLights[0].specular", 0.0f, 0.0f, 0.0f);
        shader->setFloat("spotLights[0].constant", 1.0f);
        shader->setFloat("spotLights[0].linear", 0.09);
        shader->setFloat("spotLights[0].quadratic", 0.032);
        shader->setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
        shader->setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));
    }
}