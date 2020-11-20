//
// Created by Sean on 10/3/2019.
//

#ifndef GAMEENGINE_UITESTWINDOW_H
#define GAMEENGINE_UITESTWINDOW_H

#include "UIWindow.h"

class UITestWindow : public UIWindow
{
public:
	UITestWindow(bool *box1, bool *box2, bool *box3, bool *box4);
private:
	void showWidgets(void);
	bool *show_demo_window;
	bool *show_render_window;
	bool *noise_map_viewer;
	bool *scene_info_viewer;
};


#endif //GAMEENGINE_UITESTWINDOW_H
