//
// Created by Sean on 11/26/2020.
//

#include "Editor.h"

Editor::Editor(Window *targetWindow) : mainIMGUIWindow(targetWindow)
{
	this ->testWindow = new UITestWindow(&show_demo_window, &show_render_window, &noise_map_viewer, &show_scene_window);
}

void Editor::startFrame()
{
	this->mainIMGUIWindow.startFrame();
}

void Editor::render()
{
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
//	if (show_scene_window)
//	{
//		dataWindow.render();
//	}
	this->mainIMGUIWindow.render();
}

void Editor::shutDown()
{
	this->mainIMGUIWindow.shutDown();
}
