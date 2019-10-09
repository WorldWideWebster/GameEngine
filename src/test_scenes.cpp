//
// Created by Sean on 10/8/2019.
//

#include "test_scenes.h"
#include "primitives/Sphere.h"

Scene *testScene_1 = new Scene();
Scene *testScene_2 = new Scene();

void setUpTestScene1(void)
{
	testScene_1->addEntity(new Entity(new Mesh(new Sphere(25, 25, 25)), glm::vec3(0.0f)));
}

void setUpTestScene2(void)
{
	// Terrain Generation
	// Create Noise map
	NoiseMap *nm = new NoiseMap;
	// Create texture from noise map
	Texture tx = TextureFromNoiseMap(*nm);
}