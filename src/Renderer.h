//
// Created by Sean on 9/10/2019.
//

#ifndef OPENGLSETUP_RENDERER_H
#define OPENGLSETUP_RENDERER_H

#include <memory>

#include "Scene.h"
#include "buffer-objects/ShadowDepthBuffer.h"
#include "buffer-objects/FrameBuffer.h"

class Renderer
{
public:
	Renderer();
	void addScene(Scene m_scene);
	void setActiveScene(Scene *targetScene);
	void setActiveScene(int targetSceneID);
	Scene* getActiveScene(void);
	unsigned int getRenderBufferTexture(void);
	unsigned int *getRenderBufferTexturePtr(void);
private:
	void render(Scene *targetScene);
	std::vector<Scene> m_scenes;
	Scene* m_currentActiveScene;
	FrameBuffer m_frameBuffer;
	ShadowDepthBuffer m_shadowBuffer;
};


#endif //OPENGLSETUP_RENDERER_H
