//
// Created by Sean on 10/3/2019.
//

#include "UITestWindow.h"

UITestWindow::UITestWindow(bool *box1, bool *box2, bool *box3, bool *box4)
{
	this->setName("Test Window Using UITestWindow Class");
	this->show_demo_window = box1;
	this->show_render_window = box2;
	this->noise_map_viewer = box3;
	this->scene_info_viewer = box4;
}

void UITestWindow::showWidgets(void)
{
	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Stupid Toby", show_demo_window);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Render Window", show_render_window);
	ImGui::Checkbox("Image Viewer", noise_map_viewer);
	ImGui::Checkbox("Scene Info Viewer", scene_info_viewer);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
}