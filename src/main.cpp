#define STB_IMAGE_IMPLEMENTATION
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "libs.h"

// camera
/// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 lightDir(-0.2f, -1.0f, -0.3f);

int main()
{
    Window window;


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // build and compile our shader program
    // ------------------------------------
    Shader lightingShader("../shaders/colors.vert", "../shaders/colors.frag");
    Shader terrainColorShader("../shaders/terrain_colors.vert", "../shaders/terrain_colors.frag");
    Shader lampShader("../shaders/lamp.vert", "../shaders/lamp.frag");
    Shader screenShader("../shaders/framebuffer.vert", "../shaders/framebuffer.frag");
    Shader skyboxShader("../shaders/skybox.vert", "../shaders/skybox.frag");
    Shader instanceShader("../shaders/instance.vert", "../shaders/instance.frag");
    Shader normalDisplayShader("../shaders/normal_vis.vert", "../shaders/normal_vis.frag", "../shaders/normal_vis.geom");

    GLuint uniformBlockIndexLighting = glGetUniformBlockIndex(lightingShader.ID, "Matrices");
    GLuint uniformBlockIndexLamp = glGetUniformBlockIndex(lampShader.ID, "Matrices");
    GLuint uniformBlockIndexInstance = glGetUniformBlockIndex(instanceShader.ID, "Matrices");

    glUniformBlockBinding(lightingShader.ID, uniformBlockIndexLighting, 0);
    glUniformBlockBinding(lampShader.ID, uniformBlockIndexLamp, 0);
    glUniformBlockBinding(instanceShader.ID, uniformBlockIndexInstance, 0);

    GLuint diffuseMap = loadTexture("../resources/container2.png");
    GLuint specularMap = loadTexture("../resources/container2_specular.png");
    GLuint emissionMap = loadTexture("../resources/matrix.jpg");
    GLuint floorTexture = loadTexture("../resources/metal.png");
    GLuint cubeTexture = loadTexture("../resources/container2.png");
    GLuint transparentTexture = loadTexture("../resources/window.png");

    Texture cubemapTexture = CubemapTextureFromFile(faces);

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

    RenderBuffer renderBuffer;
    // load models
    // -----------
    Model ourModel((char *) "resources/objects/nanosuit/nanosuit.obj");
    Model rock((char *) "resources/objects/rock/rock.obj");
    Model planet((char *) "resources/objects/planet/planet.obj");
    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    GLuint amount = 1000;
    glm::mat4 *modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(glfwGetTime()); // initialize random seed
    float radius = 100.0;
    float offset = 50.5f;

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
    bool noise_map_viewer = false;
    bool render_input = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float lightx = 0.5f, lighty = 0.5f, lightz = 0.50f;
    bool flashlight = false;

    // render loop

    auto newScene = std::make_unique<Scene>();
	//SkyBox skybox (cubemapTexture, newScene->getDefaultCamera(), &renderBuffer);

	window.setCamera(newScene->getDefaultCamera());
	newScene->setActiveScene();
	newScene->addEntity(new Entity(new Mesh(new Sphere(25, 25, 25)), glm::vec3(0.0f)));
	newScene->addEntity(new Entity(new Mesh(new Terrain())));
	newScene->addLight(new PointLight("pointLights[0]"));
	newScene->addLight(new SpotLight("spotLights[0]"));
	//newScene->addEntity(new Entity(new Mesh(new Sphere(10, 10, 10)), glm::vec3(0.0f)));
	//lightSphere->setScale(glm::vec3(20.0f));

	// Terrain Generation
	// Create Noise map
	NoiseMap *nm = new NoiseMap;
	// Create texture from noise map
	Texture tx = TextureFromNoiseMap(*nm);


	UITestWindow *testWindow = new UITestWindow(&show_demo_window, &show_render_window, &noise_map_viewer);
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

        // Time based variables
        lightPos = glm::vec3(1000 * cos(glfwGetTime()), 0, 1000 * sin(glfwGetTime()));
        lightDir = glm::vec3(2 , sin(glfwGetTime() / 10), cos(glfwGetTime() / 10) );

        // be sure to activate shader when setting uniforms/drawing objects
		newScene->render(&terrainColorShader, &renderBuffer);


		newScene->setLightPosition("pointLights[0]", lightPos);
		// TODO: Figure out flashlight with scene
		/*
		l->updatePosition(lightPos);
		if (flashlight)
		{
			sl->turnOn();
		}
        else
        {
			sl->turnOff();
        }
        */
		// spotLight
		// TODO: Figure out position/direction update in scene
		//sl->updatePosition(camera.Position);
		//sl->updateDirection(camera.Front);
        glm::mat4 model;

		//e->setPosition(lightPos.operator*=(2));
		// e->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
		//e->setRotation(lightPos, angle);
		//e->render(&terrainColorShader);
        // then draw model with normal visualizing geometry shader
/*
        normalDisplayShader.use();
        normalDisplayShader.setMat4("projection", renderBuffer.getProjection());
        normalDisplayShader.setMat4("view", view);
        normalDisplayShader.setMat4("model", model);
*/

        // Draw the lamp object
		//lightSphere->setPosition(lightPos);
        //lightSphere->render(&lampShader);

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

        // 3. Show another simple window.
		// TODO: move to separate file
        if (show_render_window)
        {
			ImGui::Begin("Render Window",  &show_render_window);

			ImGui::Text("Location: %f %f %f     Direction: %f %f %f", newScene->getDefaultCamera()->Position.x,
					newScene->getDefaultCamera()->Position.y, newScene->getDefaultCamera()->Position.z,
						newScene->getDefaultCamera()->Front.x, newScene->getDefaultCamera()->Front.y, newScene->getDefaultCamera()->Front.z);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
						ImGui::GetIO().Framerate);
			// Set render window position
            ImGui::SetWindowPos("Render Window", ImVec2(0, 0), ImGuiCond_FirstUseEver);
            // Set render window size
            ImGui::SetWindowSize("Render Window", ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
                                 ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y), ImGuiCond_FirstUseEver);
            // Window for rendering scene
            ImGui::Image(
                    (void *)(uintptr_t)  renderBuffer.getTextureColorbuffer(), ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y),
                    ImVec2(0,1), ImVec2(1,0), ImColor(255,255,255,255), ImColor(255,255,255,128));
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
            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_F)))
            {
                flashlight = !flashlight;
            }

            ImGui::End();
        }

        // 3. Show another simple window.
		// TODO move to separate file
        if (noise_map_viewer)
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
        }

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

