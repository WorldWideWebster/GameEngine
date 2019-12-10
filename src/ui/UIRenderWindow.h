//
// Created by Sean on 9/19/2019.
//

#ifndef OPENGLSETUP_UIRENDERWINDOW_H
#define OPENGLSETUP_UIRENDERWINDOW_H

#include <memory>
#include "UIWindow.h"
#include "../RenderBuffer.h"

// Render Window default sizes
#define  RENDER_WINDOW_DEFAULT_X 1920
#define  RENDER_WINDOW_DEFAULT_Y 1080

class UIRenderWindow : public UIWindow
{
public:
	UIRenderWindow(RenderBuffer *targetRenderBuffer, std::string Name);
	virtual void showRenderBuffer(void);
	virtual void showWidgets(void);
private:
	RenderBuffer *m_renderBuffer;
};


#endif //OPENGLSETUP_UIRENDERWINDOW_H
