//
// Created by Sean on 11/26/2020.
//

#ifndef GAMEENGINE_EDITOR_H
#define GAMEENGINE_EDITOR_H


#include <editor/ui/MainWindow.h>
#include <editor/ui/UIDataWindow.h>
#include <editor/ui/UITestWindow.h>

#include <rendering/Renderer.h>


class Editor
{
public:
	Editor(Window *targetWindow);

	void startFrame();
	void render();
	void shutDown();
private:
	MainWindow mainIMGUIWindow;
	UITestWindow *testWindow;
//	UIDataWindow dataWindow;


	Renderer *m_renderer;

	bool show_demo_window = true;
	bool show_render_window = false;
	bool show_scene_window = true;
	bool noise_map_viewer = false;

};


#endif //GAMEENGINE_EDITOR_H
