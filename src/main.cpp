#define STB_IMAGE_IMPLEMENTATION
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "libs.h"
#include <shader/shader.h>
#include <buffer-objects/ShadowDepthBuffer.h>
#include "ShadowMap.h"

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

	/*******************TEXTURE SETUP***************************/
	GLuint diffuseMap = loadTexture("../resources/container2.png");
    GLuint specularMap = loadTexture("../resources/container2_specular.png");
    GLuint emissionMap = loadTexture("../resources/matrix.jpg");
    GLuint floorTexture = loadTexture("../resources/metal.png");
    GLuint cubeTexture = loadTexture("../resources/container2.png");
    GLuint transparentTexture = loadTexture("../resources/window.png");

    Texture cubemapTexture = CubemapTextureFromFile(faces);
	/*******************TEXTURE SETUP***************************/

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
	FrameBuffer frameBuffer;

	ShadowDepthBuffer sb;
	setShadowMap(sb.getShadowMap());
	//FIXME: 2 frame buffers cancel eachother out

	UIRenderWindow renderWindow(&frameBuffer, "Render Window");
	UIRenderWindow testRenderWindow(&sb, "Test Render Window");
	renderWindow.open();
	testRenderWindow.open();
	/**********************************************/
	// TODO: Move this to window creation
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    /**********************************************/

    // Setup Platform/Renderer bindings
    const char *glsl_version = "#version 130";

    ImGui_ImplGlfw_InitForOpenGL(window.m_glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_render_window = false;
    bool show_scene_window = true;
    bool noise_map_viewer = false;
    bool render_input = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	 /// Render loop setup
		auto newScene = std::make_shared<Scene>();

		// TODO: move skybox to special entity
		//SkyBox skybox (cubemapTexture, newScene->getDefaultCamera(), &frameBuffer);

		window.setCamera(newScene->getDefaultCamera());
		setUpTestScene3(newScene);

	// TODO: move terrain to special entity
	// Terrain Generation
	// Create Noise map
/*
 * FIXME: Texture from this somehow overwrites other textures
	NoiseMap *nm = new NoiseMap;
	// Create texture from noise map
	Texture tx = TextureFromNoiseMap(*nm);
*/

	/** Shadow Stuff */
	// shadow shader configuration
	// --------------------
	shadowShader.use();
	shadowShader.setInt("diffuseTexture", 0);
	shadowShader.setInt("shadowMap", 1);
	debugDepthQuad.use();
	debugDepthQuad.setInt("depthMap", 0);
	/** Shadow Stuff */

	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

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

        // TODO: Move renderbuffer
        // TODO: Figure out how to have a single light effect multiple shaders

		// be sure to activate shader when setting uniforms/drawing objects
		doTestScene3(newScene);
		lightPos = glm::vec3(1 * cos(glfwGetTime()), 0, 1 * sin(glfwGetTime()));

		// 1. Render Depth of scene to texture (from lights perspective)
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0, far_plane = 7.5f;
		//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
		// note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		// Render scene from light's point of view
		simpleDepthShader.use();
		simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		shadowShader.use();
		shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);


/*
 * TODO: figure out what to do with the view and projection matrices
 *
 *
 /// Stuff for displaying normals
        glm::mat4 model;
        normalDisplayShader.use();
        normalDisplayShader.setMat4("projection", frameBuffer.getProjection());
        normalDisplayShader.setMat4("view", view);
        normalDisplayShader.setMat4("model", model);
*/

        // TODO: Move renderbuffer to inside scene?

        // UI stuff
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        testWindow->render();
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);


		if (show_scene_window)
		{
			std::vector<std::string> sceneDetails = newScene->showSceneDetails();
			ImGui::Begin("Scene Window",  &show_scene_window);
			for (int i = 0; i < sceneDetails.size(); i++)
			{
					ImGui::Text(sceneDetails[i].c_str());
			}
			ImGui::End();
		}

		// Render Window



		newScene->render(&simpleDepthShader, &sb);
		testRenderWindow.renderTargetImage(getShadowMap());

		newScene->render(&lightingShader, &frameBuffer);
//		newScene->render(&shadowShader, &frameBuffer);
		renderWindow.renderTargetImage(frameBuffer.getTextureBuffer());
		// FIXME: When switching to lightingShader, renderwindow shows scene,


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



        // 3. Show another simple window.
		// TODO move to separate file

/*        if (noise_map_viewer)
        {

			ImGui::Begin("Noise Map Viewer", &noise_map_viewer);       // Create a window called "Hello, world!" and append into it.

            if (ImGui::Button("GenNoise"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
				int rando = rand()%100;
				nm->reSeed(rando);
				std::cout << rando << std::endl;
				//tri->setHeightMap(nm->getData(), nm->getWidth(), nm->getHeight());
				//m = new Mesh(tri);
			}
            // Set render window position
            ImGui::SetWindowPos("Image Viewer", ImVec2(RENDER_WINDOW_DEFAULT_X, 0), ImGuiCond_FirstUseEver);
            // Set render window size
            ImGui::SetWindowSize("Image Viewer", ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
                                 ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y), ImGuiCond_FirstUseEver);
            // Window for rendering scene
            // FIXME: texture doesn't move with window
            ImGui::Image((void *)(uintptr_t)  nm->getTexID(), ImVec2(nm->getWidth(), nm->getHeight()),
                    ImVec2(0,1), ImVec2(1,0), ImColor(255,255,255,255), ImColor(255,255,255,128));
            ImGui::End();
        }*/

        ImVec2 pos = ImGui::GetCursorScreenPos();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(window.m_glfwWindow);
        glfwGetFramebufferSize(window.m_glfwWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
    ImGui::DestroyContext();

    glfwDestroyWindow(window.m_glfwWindow);
    glfwTerminate();
    return 0;
}

