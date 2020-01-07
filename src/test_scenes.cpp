//
// Created by Sean on 10/8/2019.
//

#include "test_scenes.h"
#include "primitives/Sphere.h"
#include "primitives/Terrain.h"
#include <GLFW/glfw3.h>

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 lightDir(-0.2f, -1.0f, -0.3f);

Texture woodTex;
Texture cubeTex;
Texture sand;



/*

// load models
// -----------
Model ourModel((char *) "resources/objects/nanosuit/nanosuit.obj");
Model rock((char *) "resources/objects/rock/rock.obj");
Model planet((char *) "resources/objects/planet/planet.obj");

*/


bool flashlight = false;

void toggleFlashLight(void)
{
	flashlight = !flashlight;
}

void setUpTestScene1(std::shared_ptr<Scene> targetScene)
{
	woodTex = TextureFromFile("Sand.png", "../resources", 1);
	targetScene->setActiveScene();
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Sphere(25, 25, 25)), glm::vec3(0.0f), "sphere")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Terrain(), woodTex))));
	targetScene->addLight(std::make_shared<PointLight>(PointLight("pointLights[0]")));
	targetScene->addLight(std::make_shared<Light>(Light(glm::vec3(0.5f), glm::vec3 (0.8f), glm::vec3(1.0f), "dirLights[0]")));
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

void setUpTestScene3(std::shared_ptr<Scene> targetScene)
{
	woodTex = TextureFromFile("wood.png", "../resources", 1);
	cubeTex = TextureFromFile("container2.png", "../resources/");

	targetScene->setActiveScene();
	targetScene->addLight(std::make_shared<DirectionalLight>(DirectionalLight("dirLights[0]")));
//	targetScene->addLight(std::make_shared<Light>(Light(glm::vec3(0.3f), glm::vec3 (0.2f), glm::vec3(0.5f), "dirLights[0]")));

	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, cubeTex), glm::vec3(0,2,0), "cube")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, cubeTex), glm::vec3(2,1,0), "cube_1")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, cubeTex), glm::vec3(3,0,5), "cube_2")));

	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Quad, woodTex), glm::vec3(0, 0, -0.025), "quad")));

	targetScene->setEntityRotationDeg("quad", -90, glm::vec3(1, 0, 0));
	targetScene->setEntityScale("quad", glm::vec3(20,20,20));

}


void doTestScene3(std::shared_ptr<Scene> targetScene)
{
	lightPos = glm::vec3(1 * cos(glfwGetTime()), 0, 1 * sin(glfwGetTime()));
	lightDir = glm::vec3(0, 100 * sin(glfwGetTime()), 100 * cos(glfwGetTime()));
	targetScene->setLightDirection("dirLights[0]", lightDir);


}


void setUpTestScene4(std::shared_ptr<Scene> targetScene)
{

}


void doTestScene4(std::shared_ptr<Scene> targetScene)
{
	glColor3f(.3,.3,.3);
	glBegin(GL_QUADS);
	glVertex3f( 0,-0.001, 0);
	glVertex3f( 0,-0.001,10);
	glVertex3f(10,-0.001,10);
	glVertex3f(10,-0.001, 0);
	glEnd();

	glBegin(GL_LINES);
	for(int i=0;i<=10;i++) {
		if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
		glVertex3f(i,0,0);
		glVertex3f(i,0,10);
		if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
		glVertex3f(0,0,i);
		glVertex3f(10,0,i);
	};
	glEnd();

//	glBegin (GL_LINES);
//	glVertex3f (0.0f, 0.0f, 0.0f);
//	glVertex3f (0.0f, 50.0f, 0.0f);
//	glEnd();
}




