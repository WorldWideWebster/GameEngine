//
// Created by Sean on 9/19/2019.
//

#ifndef OPENGLSETUP_UIRENDERWINDOW_H
#define OPENGLSETUP_UIRENDERWINDOW_H

#include "UIWindow.h"
#include "../Renderer.h"

// Render Window default sizes
#define  RENDER_WINDOW_DEFAULT_X 1920
#define  RENDER_WINDOW_DEFAULT_Y 1080

class UIRenderWindow : public UIWindow
{
public:
	UIRenderWindow(Renderer *targetRenderer);
	virtual void showWidgets(void);
private:
	Renderer *m_renderer;
};


#endif //OPENGLSETUP_UIRENDERWINDOW_H
