
#include "common/main_defs.h"
#include "common/libs.h"
#include <editor/Editor.h>
#include <engine/interfaces/physics/bullet/SimplePhysicsIntegration.h>


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	Window window;
	TextureLibrary texLibrary;
	TextureLibraryLocator::provide(&texLibrary);
	TextureViewer viewer;
	SimplePhysicsIntegration physicsEngine;
	Editor engineEditor(&window);

	// glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	bool render_input = true;

	 /// Render loop setup
	Renderer renderer;

	renderer.addScene(Scene());
	setUpTestScene1(renderer.getActiveScene());
	window.setCamera(renderer.getActiveScene()->getDefaultCamera());
	UIRenderWindow renderWindow(&renderer, "Render Window");
//	UIRenderWindow testRenderWindow(&renderer, "ShadowMap");
	UIDataWindow dataWindow("Data Window", renderer.getActiveScene());

	/// Initialize Physics World
	physicsEngine.initPhysics();

	glDisable( GL_CULL_FACE );
    while (!window.shouldClose())
    {
		/******************** PREFRAME LOGIC *********************/
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		engineEditor.startFrame();

		/******************** GAME LOOP *********************/
		doTestScene1(renderer.getActiveScene());

		/******************** RENDER SCENE *********************/
		renderer.renderActiveScene();

		/******************** INPUT *********************/
        window.processInput(deltaTime);
		// Capture input for render window, allow ESC to drop context(?)
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
		{
			render_input = !render_input;
		}
		if(render_input)
		{
			glfwSetInputMode(window.m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		}
		else
		{
			glfwSetInputMode(window.m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		/******************** WINDOW UPDATES *********************/
		renderWindow.render();

//		if (show_scene_window)
//		{
//			dataWindow.render();
//		}
		viewer.render();
        engineEditor.render();
        window.update();
        glfwPollEvents();
    }

    // Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	engineEditor.shutDown();

    glfwDestroyWindow(window.m_glfwWindow);
    glfwTerminate();
    return 0;
}

