//
// Created by Sean on 8/8/2019.
//

#include "Scene.h"

Scene::Scene()
{
	this->m_num_point_lights = 1;
	this->m_num_dir_lights = 0;
	this->m_num_spot_lights = 1;
}



void Scene::addEntity(Entity *targetEntity)
{
	this->m_entities.push_back(*targetEntity);
}

void Scene::addPointLight(PointLight* targetLight)
{
	this->m_p_lights.push_back(*targetLight);
}

void Scene::addDirectionalLight(DirectionalLight* targetLight)
{
	this->m_d_lights.push_back(*targetLight);
}

void Scene::addSpotLight(SpotLight* targetLight)
{
	this->m_s_lights.push_back(*targetLight);
}

void Scene::render(Shader *shader)
{
	if(this->m_active)
	{
		setShaderPointLights(shader);
		setShaderDirLights(shader);
		setShaderSpotLights(shader);

		// TODO: Move this to a function
		shader->setFloat("material.shininess", 1.0f);

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i].render(shader);
		}

		for (int i = 0; i < m_p_lights.size(); i++)
		{
			m_p_lights[i].render(shader);
		}

		for (int i = 0; i < m_d_lights.size(); i++)
		{
			m_d_lights[i].render(shader);
		}

		for (int i = 0; i < m_s_lights.size(); i++)
		{
			m_s_lights[i].render(shader);
		}
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