//
// Created by Sean on 9/19/2019.
//

#ifndef OPENGLSETUP_UIRENDERWINDOW_H
#define OPENGLSETUP_UIRENDERWINDOW_H

#include <memory>
#include "UIWindow.h"
#include "buffer-objects/FrameBuffer.h"

// Render Window default sizes
#define  RENDER_WINDOW_DEFAULT_X 1920
#define  RENDER_WINDOW_DEFAULT_Y 1080

class UIRenderWindow : public UIWindow
{
public:
	UIRenderWindow(BufferObject *targetBufferObject, std::string Name);
	virtual void showRenderBuffer(void);
	virtual void showWidgets(void);
private:
	BufferObject *m_bufferObject;
};


#endif //OPENGLSETUP_UIRENDERWINDOW_H
