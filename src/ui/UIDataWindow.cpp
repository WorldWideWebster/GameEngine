//
// Created by Sean on 1/27/2020.
//

#include "UIDataWindow.h"

UIDataWindow::UIDataWindow(std::string targetName, std::shared_ptr<Scene> targetScene)
{
	this->setName(targetName);
	this->m_scene = targetScene;
}

void UIDataWindow::showWidgets(void)
{
	std::vector<std::string> sceneDetails = this->m_scene->showSceneDetails();
	for (int i = 0; i < sceneDetails.size(); i++)
	{
		ImGui::Text(sceneDetails[i].c_str());
	}
}