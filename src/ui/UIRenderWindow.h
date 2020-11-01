//
// Created by Sean on 9/19/2019.
//

#ifndef GAMEENGINE_UIRENDERWINDOW_H
#define GAMEENGINE_UIRENDERWINDOW_H

#include <memory>
#include "UIWindow.h"
#include "buffer-objects/FrameBuffer.h"

// Render Window default sizes
#define  RENDER_WINDOW_DEFAULT_X 1920
#define  RENDER_WINDOW_DEFAULT_Y 1080

class UIRenderWindow : public UIWindow
{
public:
	UIRenderWindow(Renderer *targetRenderer, std::string Name);
	virtual void showRenderBuffer(void);
	virtual void renderTexture(unsigned int target_texture);
	virtual void showWidgets(void);
	/**
	 * @brief Menu bar logic and display for window
	 */
	virtual void showMenuBar(void);
	virtual void renderTargetImage(unsigned int target_texture);
private:
	Renderer *m_renderer;
	GLuint m_targetImage;
	bool m_skyboxToggle;

};


#endif //GAMEENGINE_UIRENDERWINDOW_H
