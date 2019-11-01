//
// Created by Sean on 9/10/2019.
//

#ifndef OPENGLSETUP_RENDERER_H
#define OPENGLSETUP_RENDERER_H

#include <memory>

#include "Scene.h"

class Renderer
{
public:
	void addScene(Scene m_scene);
	void setActiveScene(std::shared_ptr<Scene> targetScene);
	void setActiveScene(int targetSceneID);
	std::shared_ptr<Scene> getActiveScene(void);
private:
	std::vector<Scene> m_scenes;
	std::shared_ptr<Scene> m_currentActiveScene;
};


#endif //OPENGLSETUP_RENDERER_H
