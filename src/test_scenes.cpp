//
// Created by Sean on 10/8/2019.
//

#include "test_scenes.h"
#include "primitives/Sphere.h"
#include "primitives/Terrain.h"

void setUpTestScene1(std::shared_ptr<Scene> targetScene)
{
	targetScene->setActiveScene();
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Sphere(25, 25, 25)), glm::vec3(0.0f), "sphere")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Terrain()))));
	targetScene->addLight(std::make_shared<PointLight>(PointLight("pointLights[0]")));
	targetScene->addLight(std::make_shared<SpotLight>(SpotLight("spotLights[0]")));
	targetScene->getLightByID("pointLights[0]")->attachToEntity(targetScene->getEntityByID("sphere"));
}

void setUpTestScene2(void)
{
	// Terrain Generation
	// Create Noise map
	NoiseMap *nm = new NoiseMap;
	// Create texture from noise map
	Texture tx = TextureFromNoiseMap(*nm);
}