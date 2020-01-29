//
// Created by Sean on 1/27/2020.
//

#ifndef OPENGLSETUP_UIDATAWINDOW_H
#define OPENGLSETUP_UIDATAWINDOW_H
#include "UIWindow.h"
#include "../Scene.h"

class UIDataWindow : public UIWindow
{
public:
	UIDataWindow(std::string targetName, std::shared_ptr<Scene> targetScene);
private:
	void showWidgets(void);
	std::shared_ptr<Scene> m_scene;
};


#endif //OPENGLSETUP_UIDATAWINDOW_H
