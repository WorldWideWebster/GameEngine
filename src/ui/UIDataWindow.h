//
// Created by Sean on 1/27/2020.
//

#ifndef GAMEENGINE_UIDATAWINDOW_H
#define GAMEENGINE_UIDATAWINDOW_H
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


#endif //GAMEENGINE_UIDATAWINDOW_H
