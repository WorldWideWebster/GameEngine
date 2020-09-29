
#include "main_defs.h"
#include "libs.h"

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	Window window;

	// glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
	MainWindow mainIMGUIWindow(&window);


	bool show_demo_window = true;
    bool show_render_window = false;
    bool show_scene_window = true;
    bool noise_map_viewer = false;
    bool render_input = true;

	 /// Render loop setup
	Renderer renderer;

	renderer.addScene(Scene());
	setUpTestScene1(renderer.getActiveScene());
	window.setCamera(renderer.getActiveScene()->getDefaultCamera());
	UIRenderWindow renderWindow(&renderer, "Game");
	UIRenderWindow testRenderWindow(&renderer, "ShadowMap");
	UIDataWindow dataWindow("Data Window", renderer.getActiveScene());

	glDisable( GL_CULL_FACE );
	UITestWindow *testWindow = new UITestWindow(&show_demo_window, &show_render_window, &noise_map_viewer, &show_scene_window);
    while (!window.shouldClose())
    {
		/******************** PREFRAME LOGIC *********************/
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		mainIMGUIWindow.startFrame();

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
		testRenderWindow.renderTargetImage(renderer.getGBufferTex());
		testWindow->render();
		if (show_demo_window)
		{
			ImGui::ShowDemoWindow(&show_demo_window);
		}
		if (show_scene_window)
		{
			dataWindow.render();
		}

        mainIMGUIWindow.render();
        window.update();
        glfwPollEvents();
    }

    // Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	mainIMGUIWindow.shutDown();

    glfwDestroyWindow(window.m_glfwWindow);
    glfwTerminate();
    return 0;
}

