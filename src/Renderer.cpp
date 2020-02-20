//
// Created by Sean on 9/10/2019.
//

#include "Renderer.h"
#include "main_defs.h"
#include <GLFW/glfw3.h>

Renderer::Renderer()
{

}


void Renderer::addScene(Scene targetScene)
{
	targetScene.setDepthBuffer(this->getShadowBufferPtr()->getTextureBuffer());
	this->m_scenes.push_back(targetScene);
	if(m_currentActiveScene == nullptr)
	{
		setActiveScene(std::make_shared<Scene>(this->m_scenes.back()));
	}

}
void Renderer::setActiveScene(std::shared_ptr<Scene> targetScene)
{
	if(m_currentActiveScene != nullptr)
	{
		this->m_currentActiveScene->setInactiveScene();
	}
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

static glm::vec3 lightPos(-5.0f, 1.0f, -1.0f);

void Renderer::render(std::shared_ptr<Scene> targetScene)
{
//	// Setup for shadow pass
	lightPos.x = sin(glfwGetTime()/10) * 1000.0f;
	lightPos.z = cos(glfwGetTime()/10) * 1000.0f;
	lightPos.y = 100.0 + cos(glfwGetTime()) * 1.0f;
//	// 1. Render Depth of scene to texture (from lights perspective)
//
//	/***	Directional Shadow Map Stuff	***/
//	glm::mat4 lightProjection, lightView;
//	glm::mat4 lightSpaceMatrix;
//	float near_plane = 1.0f, far_plane = 15000.5f;
//	//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
//	// note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
//	lightProjection = glm::ortho(-1500.0f, 1500.0f, -1500.0f, 1500.0f, near_plane, far_plane);
//	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
//	lightSpaceMatrix = lightProjection * lightView;
//	// Render scene from light's point of view
//	// TODO: Allow for multiple lights with shaders
//	// Shadow Pass
//	targetScene->getShadowShader()->use();
//	targetScene->getShadowShader()->setMat4("lightSpaceMatrix", lightSpaceMatrix);
	/***	/Directional Shadow Map Stuff	***/
//	lightPos.x = sin(glfwGetTime() * 0.5) * 3.0;
//	lightPos.y = 0.5;
//	lightPos.z = 1.0;

	/***	Point Light Shadow Map Stuff	***/
	// 0. create depth cubemap transformation matrices
	// -----------------------------------------------
	float near_plane = 1.0f;
	float far_plane = 2500.0f;
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));




	this->m_shadowBuffer.bind();
	targetScene->getShadowShader()->use();
	for (unsigned int i = 0; i < 6; ++i)
		targetScene->getShadowShader()->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
	targetScene->getShadowShader()->setFloat("far_plane", far_plane);
	targetScene->getShadowShader()->setVec3("lightPos", lightPos);
	/***	/Point Light Shadow Map Stuff	***/
	targetScene->renderEntities(targetScene->getShadowShader());
	this->m_shadowBuffer.unbind();

	// Not shadow Section
	glm::mat4 view = targetScene->getDefaultCamera()->GetViewMatrix();
	targetScene->getDefaultShader()->use();
	targetScene->getDefaultShader()->setMat4("projection", m_frameBuffer.getProjection());
	targetScene->getDefaultShader()->setMat4("view", view);
	targetScene->getDefaultShader()->setVec3("lightPos", lightPos);
	targetScene->getDefaultShader()->setVec3("viewPos", targetScene->getDefaultCamera()->Position);
	targetScene->getDefaultShader()->setFloat("far_plane", far_plane);

	// TODO: Move this to a function
//	targetScene->getDefaultShader()->setFloat("material.shininess", 1.0f);

	// TODO: Move this to a separate function
	// TODO: Allow for multiple cameras

	m_frameBuffer.bind(view);

	targetScene->renderEntities(targetScene->getDefaultShader(), this->m_shadowBuffer.getTextureBuffer());
	targetScene->renderLights(targetScene->getDefaultShader());

	m_frameBuffer.unbind();
}

void Renderer::renderActiveScene(void)
{
	this->render(this->m_currentActiveScene);
}

unsigned int Renderer::getRenderBufferTexture(void)
{
	return this->m_frameBuffer.getTextureBuffer();
}
unsigned int* Renderer::getRenderBufferTexturePtr(void)
{
	return this->m_frameBuffer.getTextureBufferPtr();
}