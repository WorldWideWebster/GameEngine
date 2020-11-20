//
// Created by Sean on 9/13/2019.
//

#include "UIWindow.h"

UIWindow::UIWindow(void)
{
	m_window_flags = 0;
	this->no_titlebar = false;
	this->no_scrollbar = false;
	this->no_menu = false;
	this->no_move = false;
	this->no_resize = false;
	this->no_collapse = false;
	this->no_close = false;
	this->no_nav = false;
	this->no_background = false;
	this->no_bring_to_front = false;
}

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
	setWindowFlags();
	ImGui::Begin(this->m_name.c_str(), &this->m_open,this->m_window_flags);
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
		this->showMenuBar();
		this->showWidgets();
		this->stop();
	}
}

void UIWindow::setNoTitlebar(bool noTitlebar)
{
	this->no_titlebar = noTitlebar;
}

void UIWindow::setNoScrollbar(bool noScrollbar)
{
	this->no_scrollbar = noScrollbar;
}

void UIWindow::setNoMenu(bool noMenu)
{
	this->no_menu = noMenu;
}

void UIWindow::setNoMove(bool noMove)
{
	this->no_move = noMove;
}

void UIWindow::setNoResize(bool noResize)
{
	this->no_resize = noResize;
}

void UIWindow::setNoCollapse(bool noCollapse)
{
	this->no_collapse = noCollapse;
}

void UIWindow::setNoClose(bool noClose)
{
	this->no_close = noClose;
}

void UIWindow::setNoNav(bool noNav)
{
	this->no_nav = noNav;
}

void UIWindow::setNoBackground(bool noBackground)
{
	this->no_background = noBackground;
}

void UIWindow::setNoBringToFront(bool noBringToFront)
{
	this->no_bring_to_front = noBringToFront;
}

void UIWindow::setWindowFlags(void)
{
	this->m_window_flags = 0;
	if (this->no_titlebar)        this->m_window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (this->no_scrollbar)       this->m_window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!this->no_menu)           this->m_window_flags |= ImGuiWindowFlags_MenuBar;
	if (this->no_move)            this->m_window_flags |= ImGuiWindowFlags_NoMove;
	if (this->no_resize)          this->m_window_flags |= ImGuiWindowFlags_NoResize;
	if (this->no_collapse)        this->m_window_flags |= ImGuiWindowFlags_NoCollapse;
	if (this->no_nav)             this->m_window_flags |= ImGuiWindowFlags_NoNav;
	if (this->no_background)      this->m_window_flags |= ImGuiWindowFlags_NoBackground;
	if (this->no_bring_to_front)  this->m_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void UIWindow::showMenuBar(void)
{

}
