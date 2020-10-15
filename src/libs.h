//
// Created by Sean on 3/12/2019.
//

#ifndef GAMEENGINE_LIBS_H
#define GAMEENGINE_LIBS_H

// STD Library Includes
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <map>
#include <memory>


// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

/************** Engine Includes *****************/
/** Main **/
#include "rendering/camera.h"
#include "main_defs.h"
#include "rendering/mesh.h"
#include "rendering/model.h"
#include "Scene.h"
#include <shader/shader.h>
#include "image/texture.h"
#include "primitives/vertex.h"
#include "primitives/vertices.h"
#include "window.h"
#include "test_scenes.h"
#include "Entity.h"
#include "rendering/Renderer.h"

/** Buffer Objects **/
#include "buffer-objects/FrameBuffer.h"

/** Primitives **/
#include "primitives/depreciated/cube.h"
#include "primitives/Primitive.h"
#include "primitives/SkyBox.h"
#include "primitives/Sphere.h"
#include "primitives/Terrain.h"


/** Lighting **/
#include "lighting/Light.h"
#include "lighting/DirectionalLight.h"
#include "lighting/PointLight.h"
#include "lighting/SpotLight.h"

/** Noise **/
#include "noise/NoiseMap.h"
#include "noise/PerlinNoise.h"


/** UI Windows **/
#include "ui/UITestWindow.h"
#include "ui/UIRenderWindow.h"
#include "ui/MainWindow.h"
#include "ui/UIDataWindow.h"
/******* EXTERNAL LIBRARIES ********/
// STBI
#include "stb_image.h"

// IMGUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#endif //GAMEENGINE_LIBS_H
