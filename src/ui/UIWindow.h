//
// Created by Sean on 9/13/2019.
//

#ifndef OPENGLSETUP_UIWINDOW_H
#define OPENGLSETUP_UIWINDOW_H
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <string>
class UIWindow
{
public:
	/**
	 * @brief Default constructor for UIWindow
	 * 			sets all window flags to false
	 */
	UIWindow(void);
	void open(void);
	void close(void);
	void start(void);
	void stop(void);

	void openOrClose(bool open);
	void setName(std::string name);
	std::string getName(void);
	bool isOpen(void);
	virtual void showWidgets(void);

	/**
	 * @brief Menu bar logic and display for window
	 */
	virtual void showMenuBar(void);

	//virtual void setup(void);
	virtual void render(void);

	/**
	 * @brief Set window flags based on options for window
	 */
	void setWindowFlags(void);

	/**
	 * @brief Toggle title bar
	 * @param noTitlebar - bool for title bar
	 */
	void setNoTitlebar(bool noTitlebar);

	/**
	 * @brief Toggle scroll bar
	 * @param noScrollbar - bool for scroll bar
	 */
	void setNoScrollbar(bool noScrollbar);

	/**
	 * @brief Toggle for Menu
	 * @param noMenu - bool for menu
	 */
	void setNoMenu(bool noMenu);

	/**
	 * @brief Toggle for fixing window in place
	 * @param noMove - bool for movement status
	 */
	void setNoMove(bool noMove);

	/**
	 * @brief Toggle for window resize
	 * @param noResize - bool for resize status
	 */
	void setNoResize(bool noResize);

	/**
	 * @brief Toggle for collapse
	 * @param noCollapse - bool for collapse status
	 */
	void setNoCollapse(bool noCollapse);

	/**
	 * @brief Toggle for ability to close window
	 * @param noClose - bool for close status
	 */
	void setNoClose(bool noClose);

	/**
	 * @brief Toggle for Nav
	 * @param noNav - bool for nav status
	 */
	void setNoNav(bool noNav);

	/**
	 * @brief Toggle for Background
	 * @param noBackground - bool for background status
	 */
	void setNoBackground(bool noBackground);

	/**
	 * @brief Toggle for bring to front
	 * @param noBringToFront - bool for bring to front
	 */
	void setNoBringToFront(bool noBringToFront);
private:
	bool m_open;
	int m_width;
	int m_height;
	int m_posx;
	int m_posy;
	std::string m_name;

	// Window toggle effect flags
	ImGuiWindowFlags m_window_flags = 0;
	bool no_titlebar = false;
	bool no_scrollbar = true;
	bool no_menu = true;
	bool no_move = false;
	bool no_resize = false;
	bool no_collapse = false;
	bool no_close = false;
	bool no_nav = false;
	bool no_background = false;
	bool no_bring_to_front = false;
};


#endif //OPENGLSETUP_UIWINDOW_H
