//
// Created by Sean on 1/22/2020.
//

#include "MainWindow.h"




MainWindow::MainWindow(Window *targetWindow, ImGuiIO &io) : m_io(io)
{
	(void) m_io;
	this->Setup();

	// Setup Platform/Renderer bindings
	const char *glsl_version = "#version 130";
	ImGui_ImplGlfw_InitForOpenGL(targetWindow->m_glfwWindow, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}
void MainWindow::Setup()
{
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
}

void MainWindow::startFrame(void)
{
	// UI stuff
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	doMenu();
	doMainMenuBar();
}

void MainWindow::render(void)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void MainWindow::endFrame(void)
{
}

void MainWindow::shutDown(void)
{
	ImGui::DestroyContext();
}

void MainWindow::doMenu(void)
{
}

void MainWindow::doMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

