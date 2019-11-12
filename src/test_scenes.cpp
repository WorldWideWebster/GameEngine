//
// Created by Sean on 10/8/2019.
//

#include "test_scenes.h"
#include "primitives/Sphere.h"
#include "primitives/Terrain.h"
#include <GLFW/glfw3.h>

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 lightDir(-0.2f, -1.0f, -0.3f);

bool flashlight = false;

void toggleFlashLight(void)
{
	flashlight = !flashlight;
}

void setUpTestScene1(std::shared_ptr<Scene> targetScene)
{
	targetScene->setActiveScene();
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Sphere(25, 25, 25)), glm::vec3(0.0f), "sphere")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Terrain()))));
	targetScene->addLight(std::make_shared<PointLight>(PointLight("pointLights[0]")));
	targetScene->addLight(std::make_shared<SpotLight>(SpotLight("spotLights[0]")));
	targetScene->getLightByID("pointLights[0]")->attachToEntity(targetScene->getEntityByID("sphere"), glm::vec3(0,20,0));
}

void doTestScene1(std::shared_ptr<Scene> targetScene)
{
	// Time based variables
	lightPos = glm::vec3(1000 * cos(glfwGetTime()), 0, 1000 * sin(glfwGetTime()));
	lightDir = glm::vec3(2, sin(glfwGetTime() / 10), cos(glfwGetTime() / 10));

	targetScene->setEntityPosition("sphere", lightPos);
	if (flashlight)
	{
		targetScene->toggleLight("spotLights[0]", true);
	}
	else
	{
		targetScene->toggleLight("spotLights[0]", false);
	}

	targetScene->setLightPosition("spotLights[0]", targetScene->getDefaultCamera()->Position);
	targetScene->setLightDirection("spotLights[0]", targetScene->getDefaultCamera()->Front);
}

void setUpTestScene2(void)
{
	// Terrain Generation
	// Create Noise map
	NoiseMap *nm = new NoiseMap;
	// Create texture from noise map
	Texture tx = TextureFromNoiseMap(*nm);
}