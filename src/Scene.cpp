//
// Created by Sean on 8/8/2019.
//

#include "Scene.h"

Scene::Scene()
{
	this->m_num_point_lights = 1;
	this->m_num_dir_lights = 0;
	this->m_num_spot_lights = 1;

	// Default camera
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	this->m_cameras.push_back(camera);
	setDefaultCamera(0);
}



void Scene::addEntity(Entity *targetEntity)
{
	this->m_entities.push_back(*targetEntity);
}

void Scene::addLight(Light* targetLight)
{
	this->m_lights.push_back(targetLight);
}

void Scene::addCamera(void)
{
	//this->m_cameras.push_back(std::unique_ptr<Camera>);
}

void Scene::render(Shader *shader, RenderBuffer *renderBuffer)
{
	if(this->m_active)
	{
		glm::mat4 view = this->m_default_camera->GetViewMatrix();
		renderBuffer->bindAndBuffer(view);
		shader->use();
		setShaderPointLights(shader);
		setShaderDirLights(shader);
		setShaderSpotLights(shader);

		// TODO: Move this to a function
		shader->setFloat("material.shininess", 1.0f);

		// TODO: Move this to a separate function
		// TODO: Allow for multiple cameras
		shader->setVec3("viewPos", this->m_default_camera->Position);

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i].render(shader);
		}

		for (int i = 0; i < m_lights.size(); i++)
		{
			m_lights[i]->render(shader);
		}
		renderBuffer->bindDefault();
	}
}
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


void Scene::setLightPosition(std::string targetID, glm::vec3 targetPosition)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i]->updatePosition(targetPosition);
	}
}
void setLightDirection(std::string targetID, glm::vec3 targetPosition);
void setEntityPosition(std::string targetID, glm::vec3 targetPosition);
void setEntityDirection(std::string targetID, glm::vec3 targetPosition);