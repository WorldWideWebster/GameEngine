//
// Created by Sean on 9/19/2019.
//


#include <rendering/Renderer.h>
#include "UIRenderWindow.h"

UIRenderWindow::UIRenderWindow(Renderer *targetRenderer, std::string Name) : UIWindow()
{
	this->m_renderer = targetRenderer;
	setNoScrollbar(true);
	this->setName(Name);
	this->open();
	m_targetImage = this->m_renderer->getRenderBufferPtr()->getTextureBuffer();
	this->m_skyboxToggle = this->m_renderer->getActiveScene()->getSkyboxPointer();

}

void UIRenderWindow::showRenderBuffer(void)
{


//	ImGui::Text("Location: %f %f %f     Direction: %f %f %f", camera.Position.x, camera.Position.y, camera.Position.z,
//				camera.Front.x, camera.Front.y, camera.Front.z);

	// Set render window position
	ImGui::SetWindowPos(this->getName().c_str(), ImVec2(0, 0), ImGuiCond_FirstUseEver);

	// Window for rendering scene
	ImGui::Image(
			(void *) (uintptr_t) m_targetImage,
			ImGui::GetContentRegionAvail(),
			ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
	// Set render window size
	ImGui::SetWindowSize(this->getName().c_str(), ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
						 ImGuiCond_FirstUseEver);
}

void UIRenderWindow::renderTexture(unsigned int target_texture)
{
	m_targetImage = target_texture;
}

void UIRenderWindow::showWidgets(void)
{
	this->showRenderBuffer();
}

// TODO: Move all rendering to renderer before this class is done

/*
			ImGui::Begin("Render Window",  &show_render_window);

			ImGui::Text("Location: %f %f %f     Direction: %f %f %f", newScene->getDefaultCamera()->Position.x,
					newScene->getDefaultCamera()->Position.y, newScene->getDefaultCamera()->Position.z,
						newScene->getDefaultCamera()->Front.x, newScene->getDefaultCamera()->Front.y, newScene->getDefaultCamera()->Front.z);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
						ImGui::GetIO().Framerate);
			// Set render window position
            ImGui::SetWindowPos("Render Window", ImVec2(0, 0), ImGuiCond_FirstUseEver);
            // Set render window size
            ImGui::SetWindowSize("Render Window", ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
                                 ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y), ImGuiCond_FirstUseEver);
            // Window for rendering scene
            ImGui::Image(
                    (void *)(uintptr_t)  frameBuffer.getTextureBuffer(), ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
                    ImVec2(0,1), ImVec2(1,0), ImColor(255,255,255,255), ImColor(255,255,255,128));

            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_F)))
            {
				toggleFlashLight();
            }

            ImGui::End();
 */

void UIRenderWindow::renderTargetImage(unsigned int target_texture)
{
	if(this->isOpen())
	{
		this->start();
		renderTexture(target_texture);
		this->showWidgets();
		this->stop();
	}
}

void UIRenderWindow::showMenuBar(void)
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Layer"))
		{

			if (ImGui::MenuItem("Composite"))
			{
				this->m_targetImage = this->m_renderer->getRenderBufferTexture();
			}
			if (ImGui::MenuItem("Albedo"))
			{
				this->m_targetImage = this->m_renderer->getGBufferAlbedo();
			}
			if (ImGui::MenuItem("Normals"))
			{
				this->m_targetImage = this->m_renderer->getGBufferNormal();
			}
			if (ImGui::MenuItem("Position"))
			{
				this->m_targetImage = this->m_renderer->getGBufferPosition();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Skybox", NULL, &m_skyboxToggle))
			{
				this->m_renderer->getActiveScene()->toggleSkybox(m_skyboxToggle);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}
