//
// Created by Sean on 11/13/2018.
//

#include "window.h"

Window::Window()
{
    width = SCR_WIDTH;
    height = SCR_HEIGHT;
    title = "Main GL Window";

    lastX = width / 2.0f;
    lastY = height / 2.0f;
    firstMouse = true;
    polyMode = false;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (m_glfwWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }


    // glfw m_glfwWindow creation
    // --------------------
    glfwMakeContextCurrent(m_glfwWindow);

    glfwSetWindowUserPointer(m_glfwWindow, this);

    glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_glfwWindow, mouse_callback_wrapper);
    glfwSetScrollCallback(m_glfwWindow, scroll_callback_wrapper);

    // tell GLFW to capture our mouse
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::Window(std::string t, int w, int h)
{
    width = w;
    height = h;
    title = t;

    lastX = width / 2.0f;
    lastY = height / 2.0f;
    firstMouse = true;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (m_glfwWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }


    // glfw m_glfwWindow creation
    // --------------------
    glfwMakeContextCurrent(m_glfwWindow);

    glfwSetWindowUserPointer(m_glfwWindow, this);

    glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_glfwWindow, mouse_callback_wrapper);
    glfwSetScrollCallback(m_glfwWindow, scroll_callback_wrapper);

    // tell GLFW to capture our mouse
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
    glfwDestroyWindow(m_glfwWindow);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Window::processInput(float deltaTime)
{
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // glfwSetWindowShouldClose(m_glfwWindow, true);
        if (glfwGetInputMode(m_glfwWindow, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
        {
            glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_P) == GLFW_PRESS)
    {
        if (polyMode)
        {
            polyMode = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else
        {
            polyMode = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
}



int Window::shouldClose()
{
    return glfwWindowShouldClose(m_glfwWindow);
}

void Window::update()
{
    swapBuffers();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_glfwWindow);
}

int Window::getWidth()
{
    glfwGetFramebufferSize(m_glfwWindow, &width, &height);
    return width;
}

int Window::getHeight()
{
    glfwGetFramebufferSize(m_glfwWindow, &width, &height);
    return height;
}

std::string Window::getTitle()
{
    return title;
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Window::mouse_callback(double xpos, double ypos)
{

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (glfwGetInputMode(m_glfwWindow, GLFW_CURSOR) != GLFW_CURSOR_NORMAL)
    {
        camera->ProcessMouseMovement(xoffset, yoffset);
    }
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Window::scroll_callback(double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}


void Window::setCamera(Camera *cam)
{
    camera = cam;
}

void Window::render()
{
    update();
}