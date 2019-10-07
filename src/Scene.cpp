//
// Created by Sean on 8/8/2019.
//

#include "Scene.h"

Scene::Scene()
{}



void Scene::addEntity(Entity *targetEntity)
{
	m_entities.push_back(*targetEntity);
}

void Scene::render(Shader *shader)
{
	if(this->m_active)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i].render(shader);
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