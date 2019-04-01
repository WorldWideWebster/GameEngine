#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <map>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "window.h"
#include "mesh.h"
#include "vertices.h"
#include "texture.h"
#include "cube.h"
#include "triangle.h"
#include "main_defs.h"
#include <iostream>




// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 lightDir(-0.2f, -1.0f, -0.3f);

int main()
{
    Window window;

    window.setCamera(&camera);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
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
    Shader lampShader("../shaders/lamp.vert", "../shaders/lamp.frag");
    Shader screenShader("../shaders/framebuffer.vert", "../shaders/framebuffer.frag");
    Shader skyboxShader("../shaders/skybox.vert", "../shaders/skybox.frag");
    Shader instanceShader("../shaders/instance.vert", "../shaders/instance.frag");


    GLuint uniformBlockIndexLighting   =  glGetUniformBlockIndex(lightingShader.ID, "Matrices");
    GLuint uniformBlockIndexLamp   =      glGetUniformBlockIndex(lampShader.ID, "Matrices");
    GLuint uniformBlockIndexInstance   =      glGetUniformBlockIndex(instanceShader.ID, "Matrices");


    glUniformBlockBinding(lightingShader.ID,    uniformBlockIndexLighting, 0);
    glUniformBlockBinding(lampShader.ID,        uniformBlockIndexLamp, 0);
    glUniformBlockBinding(instanceShader.ID,    uniformBlockIndexInstance, 0);


    GLuint VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // plane VAO
    GLuint planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // screen quad VAO
    GLuint quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // skybox VAO
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // light Cube cubeVAO
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the correct data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the vertex attributes (only position data for our lamp)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint diffuseMap = loadTexture("../resources/container2.png");
    GLuint specularMap = loadTexture("../resources/container2_specular.png");
    GLuint emissionMap = loadTexture("../resources/matrix.jpg");
    GLuint floorTexture = loadTexture("../resources/metal.png");
    GLuint cubeTexture = loadTexture("../resources/container2.png");
    GLuint transparentTexture = loadTexture("../resources/window.png");



    GLuint cubemapTexture = loadCubemap(faces);



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


    // framebuffer configuration
    // -------------------------
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    GLuint textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);






    GLuint uboMatrices;
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // load models
    // -----------
    Model ourModel((char*)"resources/objects/nanosuit/nanosuit.obj");
    Model rock((char*)"resources/objects/rock/rock.obj");
    Model planet((char*)"resources/objects/planet/planet.obj");
    Model theCube((char*)"resources/objects/cube/cube.obj");
    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    GLuint amount = 100000;
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(glfwGetTime()); // initialize random seed
    float radius = 100.0;
    float offset = 50.5f;
    for (GLuint i = 0; i < amount; i++)
    {
        glm::mat4 model;
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.01f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = (rand() % 20) / 1000.0f + 0.005;
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    // vertex Buffer Object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    for(GLuint i = 0; i < rock.meshes.size(); i++)
    {
        GLuint VAO = rock.meshes[i].getVAO();
        glBindVertexArray(VAO);
        // vertex Attributes
        GLsizei vec4Size = sizeof(glm::vec4);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }






    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    const char* glsl_version = "#version 130";

    ImGui_ImplGlfw_InitForOpenGL(window.m_glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_render_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float lightx = 1.0f, lighty = 1.0f, lightz = 1.0f;

    Cube tri;
    Mesh m(&tri);
    // render loop
    // -----------
    while (!window.shouldClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float angle = 360.0f * sin(glfwGetTime()/100);

        // input
        // -----
        window.processInput(deltaTime);


        glm::mat4 view = camera.GetViewMatrix();
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        // render
        // ------
        // bind to framebuffer and draw scene as we normally would to color texture
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // TODO: Move lighting stuff to a separate file

        // Time based variables
        lightPos = glm::vec3(50 * cos(glfwGetTime()), 0, 50 * sin(glfwGetTime()));
        //lightDir = glm::vec3(2 * cos(glfwGetTime()), 0, 2 * sin(glfwGetTime()));

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setFloat("material.shininess", 32.0f);
        lightingShader.setInt("num_point_lights", 1);
        lightingShader.setInt("num_dir_lights", 1);
        lightingShader.setInt("num_spot_lights", 1);
        // directional light
        lightingShader.setVec3("dirLights[0].direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLights[0].ambient", lightx, lighty, lightz);
        lightingShader.setVec3("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.setVec3("dirLights[0].specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lightingShader.setVec3("pointLights[0].position", lightPos);
        lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.09);
        lightingShader.setFloat("pointLights[0].quadratic", 0.032);
        // spotLight
        lightingShader.setVec3("spotLights[0].position", camera.Position);
        lightingShader.setVec3("spotLights[0].direction", camera.Front);
        lightingShader.setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLights[0].constant", 1.0f);
        lightingShader.setFloat("spotLights[0].linear", 0.09);
        lightingShader.setFloat("spotLights[0].quadratic", 0.032);
        lightingShader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));

        // be sure to activate shader when setting uniforms/drawing objects
        instanceShader.use();
        instanceShader.setVec3("viewPos", camera.Position);
        instanceShader.setFloat("material.shininess", 32.0f);
        instanceShader.setInt("num_point_lights", 1);
        instanceShader.setInt("num_dir_lights", 1);
        instanceShader.setInt("num_spot_lights", 1);
        // directional light
        instanceShader.setVec3("dirLights[0].direction", -0.2f, -1.0f, -0.3f);
        instanceShader.setVec3("dirLights[0].ambient", 0.05f, 0.05f, 0.05f);
        instanceShader.setVec3("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f);
        instanceShader.setVec3("dirLights[0].specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        instanceShader.setVec3("pointLights[0].position", lightPos);
        instanceShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        instanceShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        instanceShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        instanceShader.setFloat("pointLights[0].constant", 1.0f);
        instanceShader.setFloat("pointLights[0].linear", 0.09);
        instanceShader.setFloat("pointLights[0].quadratic", 0.032);
        // spotLight
        instanceShader.setVec3("spotLights[0].position", camera.Position);
        instanceShader.setVec3("spotLights[0].direction", camera.Front);
        instanceShader.setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
        instanceShader.setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
        instanceShader.setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
        instanceShader.setFloat("spotLights[0].constant", 1.0f);
        instanceShader.setFloat("spotLights[0].linear", 0.09);
        instanceShader.setFloat("spotLights[0].quadratic", 0.032);
        instanceShader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
        instanceShader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));

        glm::mat4 model;
        lightingShader.use();

        // floor
        glBindVertexArray(planeVAO);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        lightingShader.setMat4("model", glm::mat4());
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);


        /*
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down
        lightingShader.setMat4("model", model);
        theCube.Draw(lightingShader);
        */

        // draw planet
        lightingShader.setMat4("model", model);
        m.Draw(lightingShader);

        // draw meteorites
        instanceShader.use();
        instanceShader.setMat4("model", model);

        glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
        for (GLuint i = 0; i < rock.meshes.size(); i++)
        {
            glBindVertexArray(rock.meshes[i].getVAO());
            glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
            glBindVertexArray(0);
        }

        lampShader.use();

        model = glm::mat4();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lampShader.setMat4("model", model);
        // Draw the lamp object
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);

        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default


        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);

        
        //screenShader.use();
        //glBindVertexArray(quadVAO);
        //glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
        // glDrawArrays(GL_TRIANGLES, 0, 6);


        // UI stuff
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Stupid Toby", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Render Window", &show_render_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_render_window)
        {
            // tell GLFW to capture our mouse
            glfwSetInputMode(window.m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            // Set render window position
            ImGui::SetWindowPos("Render Window", ImVec2(0, 0), ImGuiCond_FirstUseEver);
            // Set render window size
            ImGui::SetWindowSize("Render Window", ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(RENDER_WINDOW_DEFAULT_X, RENDER_WINDOW_DEFAULT_Y), ImGuiCond_FirstUseEver);
            ImGui::Begin("Wow! Amaze!", &show_render_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Such Window!");
            // Window for rendering scene
            ImGui::GetWindowDrawList()->AddImage(
                    (void *)textureColorbuffer, ImVec2(ImGui::GetItemRectMin().x,
                                                       ImGui::GetItemRectMin().y),
                    ImVec2(RENDER_WINDOW_DEFAULT_X,RENDER_WINDOW_DEFAULT_Y), ImVec2(0, 1), ImVec2(1, 0));
            if (ImGui::Button("Much Closing!"))
                show_render_window = false;
            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
            {
                glfwSetInputMode(window.m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                //show_render_window = false;
            }

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
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteBuffers(1, &quadVBO);
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

