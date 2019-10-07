//
// Created by Sean on 9/10/2019.
//

#ifndef OPENGLSETUP_RENDERER_H
#define OPENGLSETUP_RENDERER_H

#include "Scene.h"

class Renderer
{
public:
	void addScene(Scene m_scene);
	void setActiveScene(int id);

private:
	std::vector<Scene> m_scenes;
	int m_currentActiveScene;
};


#endif //OPENGLSETUP_RENDERER_H
