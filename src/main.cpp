#define STB_IMAGE_IMPLEMENTATION
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "libs.h"
#include <shader/shader.h>
#include <buffer-objects/ShadowDepthBuffer.h>

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    Window window;

    // TODO: Move GLAD setup to renderer setup function
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // TODO: move opengl setup to renderer setup
    // configure global opengl state
    // -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    // build and compile our shader program

	/*******************SHADER SETUP***************************/
    // ------------------------------------
    Shader lightingShader("../shaders/colors.vert", "../shaders/colors.frag");
    Shader gridShader("../shaders/grid.vert", "../shaders/grid.frag");
    Shader terrainColorShader("../shaders/terrain_colors.vert", "../shaders/terrain_colors.frag");
    Shader lampShader("../shaders/lamp.vert", "../shaders/lamp.frag");
    Shader screenShader("../shaders/framebuffer.vert", "../shaders/framebuffer.frag");
    Shader skyboxShader("../shaders/skybox.vert", "../shaders/skybox.frag");
    Shader instanceShader("../shaders/instance.vert", "../shaders/instance.frag");
    Shader normalDisplayShader("../shaders/normal_vis.vert", "../shaders/normal_vis.frag", "../shaders/normal_vis.geom");
	Shader shadowShader("../shaders/shadow_mapping.vert", "../shaders/shadow_mapping.frag");
	Shader simpleDepthShader("../shaders/shadow_mapping_depth.vert", "../shaders/shadow_mapping_depth.frag");
	Shader debugDepthQuad("../shaders/debug_quad_depth.vert", "../shaders/debug_quad_depth.frag");

    GLuint uniformBlockIndexLighting = glGetUniformBlockIndex(lightingShader.ID, "Matrices");
    GLuint uniformBlockIndexLamp = glGetUniformBlockIndex(lampShader.ID, "Matrices");
    GLuint uniformBlockIndexInstance = glGetUniformBlockIndex(instanceShader.ID, "Matrices");
    GLuint uniformBlockIndexTerrain = glGetUniformBlockIndex(terrainColorShader.ID, "Matrices");

    glUniformBlockBinding(lightingShader.ID, uniformBlockIndexLighting, 0);
    glUniformBlockBinding(lampShader.ID, uniformBlockIndexLamp, 0);
    glUniformBlockBinding(instanceShader.ID, uniformBlockIndexInstance, 0);
    glUniformBlockBinding(terrainColorShader.ID, uniformBlockIndexTerrain, 0);
	/*******************SHADER SETUP***************************/

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    lightingShader.use();
    lightingShader.setInt("texture1", 0);
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setInt("material.emission", 2);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    screenShader.use();
    screenShader.setInt("screenTexture", 0);


	MainWindow mainIMGUIWindow(&window);


	bool show_demo_window = true;
    bool show_render_window = false;
    bool show_scene_window = true;
    bool noise_map_viewer = false;
    bool render_input = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	 /// Render loop setup
	Renderer renderer;
	UIRenderWindow renderWindow(renderer.getRenderBufferPtr(), "Game");
	UIRenderWindow testRenderWindow(renderer.getShadowBufferPtr(), "ShadowMap");
	renderWindow.open();
	testRenderWindow.open();

	renderer.addScene(Scene());
	setUpTestScene1(renderer.getActiveScene());
	window.setCamera(renderer.getActiveScene()->getDefaultCamera());

	UIDataWindow dataWindow("Data Window", renderer.getActiveScene());
	dataWindow.open();
	glDisable( GL_CULL_FACE );
	UITestWindow *testWindow = new UITestWindow(&show_demo_window, &show_render_window, &noise_map_viewer, &show_scene_window);
	testWindow->open();
    while (!window.shouldClose())
    {
        // TODO: move render loop to separate file

        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float angle = 360.0f * sin(glfwGetTime() / 100);

        // input
        // -----
        window.processInput(deltaTime);

		doTestScene1(renderer.getActiveScene());
        mainIMGUIWindow.startFrame();
        testWindow->render();
        if (show_demo_window)
		{
			ImGui::ShowDemoWindow(&show_demo_window);
		}
		if (show_scene_window)
		{
			dataWindow.render();
		}

		// Render the scene
		renderer.renderActiveScene();

		// TODO: Show multiple shadowmaps, selectable, move to menu
		renderWindow.render();
		testRenderWindow.render();

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

        ImVec2 pos = ImGui::GetCursorScreenPos();

        // Rendering
        int display_w, display_h;
        glfwMakeContextCurrent(window.m_glfwWindow);
        glfwGetFramebufferSize(window.m_glfwWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        mainIMGUIWindow.render();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.update();
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    // Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	mainIMGUIWindow.shutDown();

    glfwDestroyWindow(window.m_glfwWindow);
    glfwTerminate();
    return 0;
}

