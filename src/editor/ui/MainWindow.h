//
// Created by Sean on 1/22/2020.
//

#ifndef GAMEENGINE_MAINWINDOW_H
#define GAMEENGINE_MAINWINDOW_H
#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_impl_glfw.h"
#include "dependencies/imgui/imgui_impl_opengl3.h"
#include "common/window.h"

static ImGuiIO& setupImgui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	return ImGui::GetIO();
}


class MainWindow
{
public:
	MainWindow(Window *targetWindow, ImGuiIO &io = setupImgui());
	void startFrame(void);
	void render(void);
	void endFrame(void);
	void shutDown(void);
	void doMenu(void);
	void doMainMenuBar(void);
private:
	ImGuiIO &m_io;

	void Setup();
};


#endif //GAMEENGINE_MAINWINDOW_H

