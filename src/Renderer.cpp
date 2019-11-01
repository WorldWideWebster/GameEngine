//
// Created by Sean on 9/10/2019.
//

#include "Renderer.h"

void Renderer::addScene(Scene targetScene)
{
	this->m_scenes.push_back(targetScene);
}
void Renderer::setActiveScene(std::shared_ptr<Scene> targetScene)
{
	this->m_currentActiveScene->setInactiveScene();
	this->m_currentActiveScene = targetScene;
	this->m_currentActiveScene->setActiveScene();
}
void Renderer::setActiveScene(int targetSceneID)
{
	this->m_currentActiveScene->setInactiveScene();
	this->m_scenes[targetSceneID].setActiveScene();
}

std::shared_ptr<Scene> Renderer::getActiveScene(void)
{
	return this->m_currentActiveScene;
}