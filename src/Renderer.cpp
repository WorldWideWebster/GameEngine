//
// Created by Sean on 9/10/2019.
//

#include "Renderer.h"

void Renderer::addScene(Scene targetScene)
{
	this->m_scenes.push_back(targetScene);
}
void Renderer::setActiveScene(int id)
{
	this->m_scenes[m_currentActiveScene].setInactiveScene();
	this->m_scenes[id].setActiveScene();
}