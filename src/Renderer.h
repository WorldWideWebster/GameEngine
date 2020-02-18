//
// Created by Sean on 9/10/2019.
//

#ifndef OPENGLSETUP_RENDERER_H
#define OPENGLSETUP_RENDERER_H

#include <memory>

#include "Scene.h"
#include "buffer-objects/ShadowDepthBuffer.h"
#include "buffer-objects/ShadowCubeDepthBuffer.h"
#include "buffer-objects/FrameBuffer.h"

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
	FrameBuffer* getRenderBufferPtr(void){return &this->m_frameBuffer;}
	ShadowCubeDepthBuffer* getShadowBufferPtr(void){return &this->m_shadowBuffer;}
	unsigned int *getRenderBufferTexturePtr(void);
private:
	void render(std::shared_ptr<Scene> targetScene);
	std::vector<Scene> m_scenes;
	std::shared_ptr<Scene> m_currentActiveScene;
	FrameBuffer m_frameBuffer;
	ShadowCubeDepthBuffer m_shadowBuffer;
};


#endif //OPENGLSETUP_RENDERER_H
