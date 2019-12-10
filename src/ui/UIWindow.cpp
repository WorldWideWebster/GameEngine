//
// Created by Sean on 9/13/2019.
//

#include "UIWindow.h"

void UIWindow::open(void)
{
	this->m_open = true;
}
void UIWindow::close(void)
{
	this->m_open = false;
}

void UIWindow::start(void)
{
	ImGui::Begin(this->m_name.c_str(), &m_open);
}
void UIWindow::stop(void)
{
	ImGui::End();
}

void UIWindow::setName(std::string name)
{
	this->m_name = name;
}

std::string UIWindow::getName(void)
{
	return this->m_name;
}

bool UIWindow::isOpen(void)
{
	return this->m_open;
}

void UIWindow::openOrClose(bool open)
{
	this->m_open = open;
}

void UIWindow::showWidgets(void)
{
	ImGui::Text("Test Window");
}

void UIWindow::render(void)
{
	if(this->isOpen())
	{
		this->start();
		this->showWidgets();
		this->stop();
	}
}