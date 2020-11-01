//
// Created by Sean on 10/9/2020.
//

#include "ModelViewer.h"

ModelViewer::ModelViewer() : UIRenderWindow(&this->m_renderer, "Model Viewer")
{
	this->m_renderer.addScene(this->m_scene);
	this->m_skyboxToggle = this->m_scene.getSkyboxPointer();

}

void ModelViewer::setModel(Model *targetModel)
{
	this->m_scene.addEntity(std::make_shared<Entity>(Entity(targetModel)));
}

void ModelViewer::showMenuBar(void)
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Demo Shapes"))
		{
			if (ImGui::MenuItem("Terrain"))
			{
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Skybox", NULL, &m_skyboxToggle))
			{
				this->m_scene.toggleSkybox(m_skyboxToggle);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}}
