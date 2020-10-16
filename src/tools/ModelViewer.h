//
// Created by Sean on 10/9/2020.
//

#ifndef GAMEENGINE_MODELVIEWER_H
#define GAMEENGINE_MODELVIEWER_H

#include <rendering/model.h>
#include <rendering/Renderer.h>
#include <ui/UIRenderWindow.h>

class ModelViewer : public UIRenderWindow
{
public:
	ModelViewer();
	void setModel(Model *targetModel);
private:
	Renderer m_renderer;
	Scene m_scene;
};


#endif //GAMEENGINE_MODELVIEWER_H
