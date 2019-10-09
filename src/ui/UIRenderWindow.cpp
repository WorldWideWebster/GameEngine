//
// Created by Sean on 9/19/2019.
//


#include "UIRenderWindow.h"

UIRenderWindow::UIRenderWindow(Renderer *targetRenderer)
{
	this->m_renderer = targetRenderer;
}

void UIRenderWindow::showWidgets(void)
{

/*
	ImGui::Text("Location: %f %f %f     Direction: %f %f %f", camera.Position.x, camera.Position.y, camera.Position.z,
				camera.Front.x, camera.Front.y, camera.Front.z);

// Set render window position
	ImGui::SetWindowPos("Render Window", ImVec2(0, 0), ImGuiCond_FirstUseEver);
// Set render window size
	ImGui::SetWindowSize("Render Window", ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
						 ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y), ImGuiCond_FirstUseEver);
// Window for rendering scene
	ImGui::Image(
			(void *) (uintptr_t) renderBuffer.getTextureColorbuffer(),
			ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
			ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
	{
		render_input = !render_input;
	}
	if (render_input)
	{
		glfwSetInputMode(window.m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	}
	else
	{
		glfwSetInputMode(window.m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_F)))
	{
		flashlight = !flashlight;
	}
*/
}

// TODO: Move all rendering to renderer before this class is done