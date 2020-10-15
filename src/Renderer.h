//
// Created by Sean on 9/10/2019.
//

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

#include <memory>

#include <Scene.h>
#include <buffer-objects/ShadowDepthBuffer.h>
#include <buffer-objects/ShadowCubeDepthBuffer.h>
#include <buffer-objects/FrameBuffer.h>
#include <buffer-objects/gBuffer.h>

class Renderer
{
public:
	Renderer();
	void addScene(Scene m_scene);
	void setActiveScene(std::shared_ptr<Scene> targetScene);
	void setActiveScene(int targetSceneID);
	void renderActiveScene(void);

	std::shared_ptr<Scene>  getActiveScene(void);
	unsigned int getRenderBufferTexture(void);
	unsigned int getGBufferNormal(void);
	unsigned int getGBufferAlbedo(void);
	unsigned int getGBufferPosition(void);
	BufferObject* getRenderBufferPtr(void){return &this->m_frameBuffer;}
	ShadowCubeDepthBuffer* getShadowBufferPtr(void){return &this->m_shadowBuffer;}
	unsigned int *getRenderBufferTexturePtr(void);
private:
	void render(std::shared_ptr<Scene> targetScene);
	std::vector<Scene> m_scenes;
	std::shared_ptr<Scene> m_currentActiveScene;
	FrameBuffer m_frameBuffer;
	gBuffer m_gBuffer;
	ShadowCubeDepthBuffer m_shadowBuffer;

	void blitDepthBuffer(void);
	void geometryPass(std::shared_ptr<Scene> targetScene);
	void lightingPass(std::shared_ptr<Scene> targetScene);
	void shadowPass(std::shared_ptr<Scene> targetScene);
};


#endif //GAMEENGINE_RENDERER_H
