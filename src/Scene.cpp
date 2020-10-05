//
// Created by Sean on 8/8/2019.
//

#include <iterator>
#include "Scene.h"
#include <GLFW/glfw3.h>

// Max light definitions
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10
#define MAX_DIR_LIGHTS 10

Scene::Scene()
{
	this->m_num_point_lights = 0;
	this->m_num_dir_lights = 0;
	this->m_num_spot_lights = 0;

	// Default camera
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	this->m_cameras.push_back(camera);
	setDefaultCamera(0);


	//TODO: Move this somewhere else when I find a place
	/** Shadow Stuff */
	// shadow shader configuration
	// --------------------
//	m_defaultShader = Shader("../shaders/shadow_mapping.vert", "../shaders/shadow_mapping.frag");
//	m_shadowShader = Shader("../shaders/shadow_mapping_depth.vert", "../shaders/shadow_mapping_depth.frag");
	m_defaultShader = Shader("../shaders/normals_point_shadows.vert", "../shaders/normals_point_shadows.frag");
	m_geomPass = Shader("../shaders/g_buffer.vert", "../shaders/g_buffer.frag");
	m_lightingPass = Shader("../shaders/deferred_shader.vert", "../shaders/deferred_shader.frag");
	m_shadowShader = Shader("../shaders/point_shadows_depth.vert", "../shaders/point_shadows_depth.frag", "../shaders/point_shadows_depth.geom");


	// TODO: Tie this into ifdef for deferred rendering
	m_lightingPass.use();
	m_lightingPass.setInt("gPosition", 0);
	m_lightingPass.setInt("gNormal", 1);
	m_lightingPass.setInt("gAlbedo", 2);
	m_lightingPass.setInt("gSpec", 3);
	m_lightingPass.setInt("depthMap", 4);
}
// TODO: Move this when I need to find another place for it
void Scene::setDepthBuffer(unsigned int depthBuffer)
{
	m_defaultShader.use();
	m_defaultShader.setInt("depthMap", depthBuffer);
	// TODO: Change this to a number similar to
	//	glActiveTexture(GL_TEXTURE4);
	//	glBindTexture(GL_TEXTURE_CUBE_MAP, this->getShadowBufferPtr()->getTextureBuffer());
}


void Scene::addEntity(std::shared_ptr<Entity> targetEntity)
{
	this->m_entities.push_back(targetEntity);
}

void Scene::addLight(std::shared_ptr<Light> targetLight)
{
	if(typeid(*targetLight) == typeid(DirectionalLight))
	{
		if(this->m_num_dir_lights < MAX_DIR_LIGHTS)
		{
			m_num_dir_lights++;
			std::cout << "dir light added" << std::endl;
		}
		else
		{
			std::cout << "Max dir light limit hit" << std::endl;
		}
	}
	else if(typeid(*targetLight) == typeid(PointLight))
	{
		if(this->m_num_point_lights < MAX_DIR_LIGHTS)
		{
			m_num_point_lights++;
			std::cout << "point light added" << std::endl;
		}
		else
		{
			std::cout << "Max point light limit hit" << std::endl;
		}
	}
	else if(typeid(*targetLight) == typeid(SpotLight))
	{
		if(this->m_num_spot_lights < MAX_DIR_LIGHTS)
		{
			m_num_spot_lights++;
			std::cout << "spot light added" << std::endl;
		}
		else
		{
			std::cout << "Max spot light limit hit" << std::endl;
		}
	}
	else
	{
		std::cout << "not a known light type!" << std::endl;
		return;
	}
	this->m_lights.push_back(targetLight);
}

void Scene::addCamera(void)
{
	//this->m_cameras.push_back(std::unique_ptr<Camera>);
}

// TODO: Should entities be grouped by shader?
void Scene::renderEntities(Shader* shader)
{
	for (int i = 0; i < this->m_entities.size(); i++)
	{
		this->m_entities[i]->render(shader);
	}
}

void Scene::renderLights(Shader* shader)
{
//	shader->use();
	setShaderPointLights(shader);
	setShaderDirLights(shader);
	setShaderSpotLights(shader);
	for (int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i]->render(shader);
	}
}

void Scene::setShadowLightPos(Shader* shadowShader)
{
	shadowShader->use();

	for (int i = 0; i < m_lights.size(); i++)
	{
		shadowShader->setVec3("lightPos", typeid(*m_lights[i]) == typeid(DirectionalLight) ? m_lights[i]->getDirection() : m_lights[i]->getPosition());
	}
}
void Scene::renderEntities(Shader* shader, unsigned int depthMap)
{
	for (int i = 0; i < this->m_entities.size(); i++)
	{
		this->m_entities[i]->render(shader, depthMap);
	}
}


static glm::vec3 lightPos(-5.0f, 1.0f, -1.0f);

void Scene::setActiveScene(void)
{
	this->m_active = true;
}
void Scene::setInactiveScene(void)
{
	this->m_active = false;
}

void Scene::setNumberOfPointLights(int numLights)
{
	this->m_num_point_lights = numLights;
}
void Scene::setNumberOfDirLights(int numLights)
{
	this->m_num_dir_lights = numLights;
}
void Scene::setNumberOfSpotLights(int numLights)
{
	this->m_num_spot_lights = numLights;
}
void Scene::setShaderPointLights(Shader *shader)
{
	shader->setInt("u_num_point_lights", m_num_point_lights);
}
void Scene::setShaderDirLights(Shader *shader)
{
	shader->setInt("u_num_dir_lights", m_num_dir_lights);
}
void Scene::setShaderSpotLights(Shader *shader)
{
	shader->setInt("u_num_spot_lights", m_num_spot_lights);
}

void Scene::setDefaultCamera(int cameraNum)
{
	if(cameraNum < this->m_cameras.size())
	{
		m_default_camera = std::make_shared<Camera>(this->m_cameras[cameraNum]);
	}
}


std::shared_ptr<Camera> Scene::getDefaultCamera(void)
{
	return m_default_camera;
}



std::shared_ptr<Entity> Scene::getEntityByID(std::string targetID)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID == targetID)
		{
			return m_entities[i];
		}
	}
	return m_entities[0];
}
std::shared_ptr<Light> Scene::getLightByID(std::string targetID)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			return m_lights[i];
		}
	}

	return m_lights[0];
}


void Scene::setLightPosition(std::string targetID, glm::vec3 targetPosition)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			m_lights[i]->updatePosition(targetPosition);
			return;
		}
	}
}


void Scene::setLightDirection(std::string targetID, glm::vec3 targetDirection)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			m_lights[i]->updateDirection(targetDirection);
			return;
		}
	}
}

void Scene::toggleLight(std::string targetID, bool toggle)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			m_lights[i]->toggle(toggle);
			return;
		}
	}
}

// TODO: Figure out why this is not working

void Scene::setEntityPosition(std::string targetID, glm::vec3 targetPosition)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID.compare(targetID) == 0)
		{
			m_entities[i]->setPosition(targetPosition);
			return;
		}
	}
}
void Scene::setEntityRotationDeg(std::string targetID, float targetRotAngle, glm::vec3 targetRotation)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID == targetID)
		{
			m_entities[i]->setRotation(targetRotAngle, targetRotation);
			return;
		}
	}
}

void Scene::setEntityScale(std::string targetID, glm::vec3 targetScale)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID == targetID)
		{
			m_entities[i]->setScale(targetScale);
			return;
		}
	}
}



std::vector<std::string> Scene::showSceneDetails(void)
{
	std::vector<std::string> returnString;
	for (int i = 0; i < m_entities.size(); i++)
	{
		std::string info;
		info = m_entities[i]->m_ID + ": " +
				"\nPosition: " +glm::to_string(m_entities[i]->getPosition()) +
				"\nRotation: " +glm::to_string(m_entities[i]->getRotation()) +
				"\nScale:	 " +glm::to_string(m_entities[i]->getScale());
		returnString.push_back(info);
	}
	for (int i = 0; i < m_lights.size(); i++)
	{
		std::string info;
		info = m_lights[i]->m_ID + ": " +
			   "\nPosition: " +glm::to_string(m_lights[i]->getPosition()) +
			   "\nDirection: " +glm::to_string(m_lights[i]->getDirection());
		returnString.push_back(info);
	}
	return returnString;
}

void Scene::toggleLightShadow(std::string targetID, bool toggle)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			m_lights[i]->toggleShadowCast(toggle);
			return;
		}
	}
}

void Scene::setSkybox(std::shared_ptr<SkyBox> skybox)
{
	this->m_has_skybox = TRUE;
	this->m_skybox = skybox;
}

void Scene::renderSkyBox()
{
	if(this->m_has_skybox)
		this->m_skybox->render();
}
