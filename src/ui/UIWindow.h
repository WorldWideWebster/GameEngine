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
	void open(void);
	void close(void);
	void start(void);
	void stop(void);

	void openOrClose(bool open);
	void setName(std::string name);
	std::string getName(void);
	bool isOpen(void);
	virtual void showWidgets(void);

	//virtual void setup(void);
	void render(void);
private:
	bool m_open;
	int m_width;
	int m_height;
	int m_posx;
	int m_posy;
	std::string m_name;
};


#endif //OPENGLSETUP_UIWINDOW_H
