//
// Created by Sean on 11/13/2018.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/camera.h"
#include "main_defs.h"

#include <iostream>
#include <string>
#include <memory>


class Window
{
public:
    Window();
    Window(std::string t, int w, int h);
    ~Window();
    void setCamera(std::shared_ptr<Camera> cam);
    void processInput(float deltaTime);
    int shouldClose();
    int getWidth();
    int getHeight();
    GLFWwindow *m_glfwWindow;
    std::string getTitle();
    void update();
    void render();
private:
    std::string title;
    int width;
    int height;
    float lastX;
    float lastY;
    bool polyMode; // flag for polygon mode
    bool firstMouse;
	std::shared_ptr<Camera> camera;
    void mouse_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);
    void swapBuffers();

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------

    static inline void framebuffer_size_callback(GLFWwindow* win, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }


    static inline void scroll_callback_wrapper(GLFWwindow *win, double xoffset, double yoffset)
    {
        Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
        window->scroll_callback(xoffset, yoffset);
    }


    static inline void mouse_callback_wrapper(GLFWwindow *win, double xpos, double ypos)
    {
        Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
        window->mouse_callback(xpos, ypos);
    }

};

#endif //WINDOW_H
