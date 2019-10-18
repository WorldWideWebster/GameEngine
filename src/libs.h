//
// Created by Sean on 3/12/2019.
//

#ifndef OPENGLSETUP_LIBS_H
#define OPENGLSETUP_LIBS_H

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
#include <GLFW/glfw3.h>

/************** Engine Includes *****************/
/** Main **/
#include "camera.h"
#include "main_defs.h"
#include "mesh.h"
#include "model.h"
#include "RenderBuffer.h"
#include "Scene.h"
#include "shader.h"
#include "texture.h"
#include "vertex.h"
#include "vertices.h"
#include "window.h"

#include "Entity.h"

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

/******* EXTERNAL LIBRARIES ********/
// STBI
#include "stb_image.h"

// IMGUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#endif //OPENGLSETUP_LIBS_H
