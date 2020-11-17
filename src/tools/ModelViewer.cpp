//
// Created by Sean on 10/9/2020.
//

#include "ModelViewer.h"
#include <primitives/Terrain.h>
#include <image/TextureLibrary.h>

ModelViewer::ModelViewer() : UIRenderWindow(new Renderer, "Model Viewer")
{
	this->m_renderer.addScene(this->m_scene);
	this->m_skyboxToggle = this->m_scene.getSkyboxPointer();
	this->m_renderer.getActiveScene()->addEntity(std::make_shared<Entity>(Entity(new Mesh(
			new Terrain(), *TextureLibraryLocator::getTextureLibrary().getTexture("stone_antelopeCayon_01_basecolor.jpg")),
																				 glm::vec3(-1000.0f, -100, -1000), "terrain")));
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
				this->m_renderer.getActiveScene()->clear();
				this->m_renderer.getActiveScene()->addEntity(std::make_shared<Entity>(Entity(new Mesh(
						new Terrain(), *TextureLibraryLocator::getTextureLibrary().getTexture("stone_antelopeCayon_01_basecolor.jpg")),
								glm::vec3(-1000.0f, -100, -1000), "terrain")));
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
	}
}
