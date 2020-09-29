//
// Created by Sean on 9/10/2019.
//

#include "Renderer.h"
#include "main_defs.h"
#include <GLFW/glfw3.h>

Renderer::Renderer()
{
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    // build and compile our shader program
}
void renderQuad();


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
#ifdef DEFERRED_RENDERING
	/** 		FORWARD RENDERING			**/
	// shadow Section
	float far_plane = 2500.0f;	// TODO: Move this
	shadowPass(targetScene);

	// Not shadow Section
	glm::mat4 view = targetScene->getDefaultCamera()->GetViewMatrix();
	targetScene->getDefaultShader()->use();
	targetScene->getDefaultShader()->setMat4("projection", m_frameBuffer.getProjection());
	targetScene->getDefaultShader()->setMat4("view", view);
	targetScene->getDefaultShader()->setVec3("viewPos", targetScene->getDefaultCamera()->Position);
	targetScene->getDefaultShader()->setFloat("far_plane", far_plane);
	targetScene->renderLights(targetScene->getDefaultShader());

	m_frameBuffer.bind();
	targetScene->renderEntities(targetScene->getDefaultShader(), this->m_shadowBuffer.getTextureBuffer());
	m_frameBuffer.unbind();

#else
	/** 		DEFERRED RENDERING			**/
	shadowPass(targetScene);
	geometryPass(targetScene);
	lightingPass(targetScene);
#endif
}

void Renderer::renderActiveScene(void)
{
	this->render(this->m_currentActiveScene);
}

unsigned int Renderer::getRenderBufferTexture(void)
{
	return this->m_frameBuffer.getTextureBuffer();
}

unsigned int Renderer::getGBufferTex(void)
{
	return this->m_gBuffer.getNormal();
}
unsigned int* Renderer::getRenderBufferTexturePtr(void)
{
	return this->m_frameBuffer.getTextureBufferPtr();
}

void Renderer::geometryPass(std::shared_ptr<Scene> targetScene)
{

	this->m_gBuffer.bindForWriting();
	glm::mat4 view = targetScene->getDefaultCamera()->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(targetScene->getDefaultCamera()->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	targetScene->getGeomShader()->use();
	targetScene->getGeomShader()->setMat4("projection", m_frameBuffer.getProjection());
	targetScene->getGeomShader()->setMat4("view", view);
	targetScene->renderEntities(targetScene->getGeomShader());
}

void Renderer::lightingPass(std::shared_ptr<Scene> targetScene)
{
	float far_plane = 2500.0f;
	this->m_frameBuffer.bind();
	targetScene->getLightingShader()->use();
	this->m_gBuffer.bindTextures();
	this->m_shadowBuffer.bindDepthMapTexture();
	targetScene->getLightingShader()->setVec3("viewPos", targetScene->getDefaultCamera()->Position);
	targetScene->getLightingShader()->setFloat("far_plane", far_plane);
	targetScene->renderLights(targetScene->getLightingShader());
	renderQuad();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_gBuffer.getID());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->m_frameBuffer.getID()); // write to default framebuffer
	glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

	this->m_frameBuffer.unbind();
}

void Renderer::shadowPass(std::shared_ptr<Scene> targetScene)
{
	// Setup for shadow pass
	lightPos.x = sin(glfwGetTime() / 10) * 1000.0f;
	lightPos.z = cos(glfwGetTime() / 10) * 1000.0f;
	lightPos.y = 100.0 + cos(glfwGetTime()) * 1.0f;
	// Render scene from light's point of view
	// TODO: Allow for multiple lights with shaders
	/***	Point Light Shadow Map Stuff	***/
	// create depth cubemap transformation matrices
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
	targetScene->setShadowLightPos(targetScene->getShadowShader());
	/***	/Point Light Shadow Map Stuff	***/
	targetScene->renderEntities(targetScene->getShadowShader());
	this->m_shadowBuffer.unbind();
}
// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
