//
// Created by Sean on 8/8/2019.
//

#include "Scene.h"

Scene::Scene()
{}



void Scene::addEntity(Entity targetEntity)
{
	entities.push_back(targetEntity);
}

void Scene::render(Shader *shader)
{
	for(int i = 0; i < entities.size(); i++)
	{
		entities[i].render(shader);
	}
}