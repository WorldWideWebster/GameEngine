//
// Created by Sean on 10/9/2020.
//

#ifndef GAMEENGINE_MODELVIEWER_H
#define GAMEENGINE_MODELVIEWER_H

#include <rendering/model.h>
#include <rendering/Renderer.h>
#include <editor/ui/UIRenderWindow.h>


// TODO: To fix this class, a lot needs to be done in regards to default settings of scene, shader, and renderer

class ModelViewer : public UIRenderWindow
{
public:
	ModelViewer();
	void setModel(Model *targetModel);
	void showMenuBar(void);
private:
	Renderer m_renderer;
	Scene m_scene;
	bool m_skyboxToggle;
};


#endif //GAMEENGINE_MODELVIEWER_H
