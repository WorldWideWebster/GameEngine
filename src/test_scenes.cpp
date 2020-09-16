//
// Created by Sean on 10/8/2019.
//

#include "test_scenes.h"
#include "primitives/Sphere.h"
#include "primitives/Terrain.h"
#include <GLFW/glfw3.h>



Texture woodTex;
Texture stonebrick;
Texture stonebrickNorm;
Texture sand;
Texture cubeTex;

Texture brick;
Texture brickNorm;
Texture brickHeight;
Texture blankHeight;

Texture stone;
Texture stoneNorm;
Texture stoneHeight;

/*

// load models
// -----------
Model ourModel((char *) "resources/objects/nanosuit/nanosuit.obj");
Model rock((char *) "resources/objects/rock/rock.obj");
Model planet((char *) "resources/objects/planet/planet.obj");

*/
/*******************TEXTURE SETUP***************************/
//GLuint diffuseMap = loadTexture("../resources/container2.png");
//GLuint specularMap = loadTexture("../resources/container2_specular.png");
//GLuint emissionMap = loadTexture("../resources/matrix.jpg");
//GLuint floorTexture = loadTexture("../resources/metal.png");
//GLuint cubeTexture = loadTexture("../resources/container2.png");
//GLuint transparentTexture = loadTexture("../resources/window.png");
//
//Texture cubemapTexture = CubemapTextureFromFile(faces);
/*******************TEXTURE SETUP***************************/

bool flashlight = false;

void toggleFlashLight(void)
{
	flashlight = !flashlight;
}

void setUpTestScene1(std::shared_ptr<Scene> targetScene)
{
////	woodTex = TextureFromFile("desert_sand.jpg", "../resources");
//	stonebrick = TextureFromFile("brickwall.jpg", "../resources");
//	stonebrickNorm = TextureFromFile("brickwall_normal.jpg", "../resources", "texture_normal");
//	blankHeight = TextureFromFile("blank_height_map.jpg", "../resources", "texture_height");
//	std::vector<Texture> brickTex;
//	brickTex.push_back(stonebrick);
//	brickTex.push_back(stonebrickNorm);
//	brickTex.push_back(blankHeight);


	stone = TextureFromFile("stone_antelopeCayon_01_basecolor.jpg", "../resources");
	stoneNorm = TextureFromFile("stone_antelopeCayon_01_normal.jpg", "../resources", "texture_normal");
	stoneHeight = TextureFromFile("stone_antelopeCayon_01_height.jpg", "../resources", "texture_height");
	stoneHeight = TextureFromFile("stone_antelopeCayon_01_metallic.jpg", "../resources", "texture_specular");
	std::vector<Texture> stoneTex;
	stoneTex.push_back(stone);
	stoneTex.push_back(stoneNorm);
	stoneTex.push_back(blankHeight);


//	brick = TextureFromFile("bricks2.jpg", "../resources");
//	brickNorm = TextureFromFile("bricks2_normal.jpg", "../resources", "texture_normal");
//	brickHeight = TextureFromFile("bricks2_disp.jpg", "../resources", "texture_height");
//	std::vector<Texture> redBrickTex;
//	redBrickTex.push_back(brick);
//	redBrickTex.push_back(brickNorm);
//	redBrickTex.push_back(brickHeight);

	targetScene->setActiveScene();
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Sphere(25, 25, 25), stoneTex), glm::vec3(20.0f, 0, 0), "sphere")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Terrain(), stoneTex), glm::vec3(-1000.0f, -100, -1000), "terrain")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, stoneTex), glm::vec3(0,0,20), "cube")));

	targetScene->setEntityScale("cube", glm::vec3(20,20,20));
	//	targetScene->addLight(std::make_shared<PointLight>(PointLight("pointLights[0]")));
	targetScene->addLight(std::make_shared<DirectionalLight>(DirectionalLight(glm::vec3(1.0f), "dirLights[0]")));
	targetScene->toggleLightShadow("dirLights[0]", true);
//	targetScene->addLight(std::make_shared<SpotLight>(SpotLight("spotLights[0]")));
//	targetScene->getLightByID("pointLights[0]")->attachToEntity(targetScene->getEntityByID("sphere"), glm::vec3(0,20,0));
//	targetScene->setEntityScale("sphere", glm::vec3(20,20,20));

}

void doTestScene1(std::shared_ptr<Scene> targetScene)
{
	// Time based variables
	glm::vec3 lightPos;
	lightPos.x = sin(glfwGetTime() / 10) * 1000.0f;
	lightPos.z = cos(glfwGetTime() / 10) * 1000.0f;
	lightPos.y = 100.0 + cos(glfwGetTime()) * 1.0f;
//
//	targetScene->setEntityPosition("sphere", lightPos);
//	if (flashlight)
//	{
//		targetScene->toggleLight("spotLights[0]", true);
//	}
//	else
//	{
//		targetScene->toggleLight("spotLights[0]", false);
//	}
//
//	targetScene->setLightPosition("spotLights[0]", lightPos);
//	targetScene->setLightDirection("spotLights[0]", targetScene->getDefaultCamera()->Front);
//	targetScene->setLightPosition("pointLights[0]", lightPos);
	targetScene->setLightDirection("dirLights[0]", lightPos);
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
	stonebrick = TextureFromFile("brickwall.jpg", "../resources");
	stonebrickNorm = TextureFromFile("brickwall_normal.jpg", "../resources", "texture_normal");
	std::vector<Texture> tex_vec;
	tex_vec.push_back(stonebrick);
	tex_vec.push_back(stonebrickNorm);

	targetScene->setActiveScene();
//	targetScene->addLight(std::make_shared<DirectionalLight>(DirectionalLight("dirLights[0]")));
//	targetScene->addLight(std::make_shared<Light>(Light(glm::vec3(0.3f), glm::vec3 (0.2f), glm::vec3(0.5f), "dirLights[0]")));
	targetScene->addLight(std::make_shared<PointLight>(PointLight("pointLights[0]")));

	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, tex_vec), glm::vec3(0,0,0), "cube")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, tex_vec), glm::vec3(2,0,0), "cube_1")));
	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, tex_vec), glm::vec3(3,0,5), "cube_2")));
//	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Cube, sand), glm::vec3(3,0,5), "cube_3")));

	targetScene->addEntity(std::make_shared<Entity>(Entity(new Mesh(new Quad, tex_vec), glm::vec3(0, 0, -0.025), "quad")));

	targetScene->setEntityRotationDeg("quad", -90, glm::vec3(1, 0, 0));
	targetScene->setEntityScale("quad", glm::vec3(20,20,20));

}


void doTestScene3(std::shared_ptr<Scene> targetScene)
{
	glm::vec3 lightPos;
	lightPos.x = sin(glfwGetTime() / 1) * 10.0f;
	lightPos.z = cos(glfwGetTime() / 1) * 10.0f;
	lightPos.y = cos(glfwGetTime() / 1) * 10.0f;
//	lightPos = glm::vec3(1 * cos(glfwGetTime()), 0, 1 * sin(glfwGetTime()));
//	lightDir = glm::vec3(0, 100 * sin(glfwGetTime()), 100 * cos(glfwGetTime()));
//	targetScene->setLightDirection("dirLights[0]", lightDir);
//	targetScene->setEntityPosition("cube_3", glm::vec3(sin(glfwGetTime() * 0.5) * 3.0, 0, 1));
	targetScene->setLightPosition("pointLights[0]", lightPos);

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




