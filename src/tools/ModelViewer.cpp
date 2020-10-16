//
// Created by Sean on 10/9/2020.
//

#include "ModelViewer.h"

ModelViewer::ModelViewer() : UIRenderWindow(&this->m_renderer, "Model Viewer")
{
	this->m_renderer.addScene(this->m_scene);
}

void ModelViewer::setModel(Model *targetModel)
{
	this->m_scene.addEntity(std::make_shared<Entity>(Entity(targetModel)));
}
