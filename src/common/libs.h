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
#include <rendering/camera.h>
#include <common/main_defs.h>
#include <rendering/mesh.h>
#include <rendering/model.h>
#include <engine/Scene.h>
#include <rendering/shader/shader.h>
#include <rendering/image/texture.h>
#include <rendering/image/TextureLibrary.h>
#include <editor/tools/TextureViewer.h>
//#include <rendering/primitives/vertex.h>
//#include <rendering/primitives/vertices.h>
#include <common/window.h>
#include <common/test_scenes.h>
#include <engine/Entity.h>
#include <rendering/Renderer.h>

/** Buffer Objects **/
#include <rendering/buffer-objects/FrameBuffer.h>

/** Primitives **/
//#include <rendering/primitives/depreciated/cube.h>
//#include <rendering/primitives/Primitive.h>
//#include <rendering/primitives/SkyBox.h>
//#include <rendering/primitives/Sphere.h>
//#include <rendering/primitives/Terrain.h>


/** Lighting **/
#include <rendering/lighting/Light.h>
#include <rendering/lighting/DirectionalLight.h>
#include <rendering/lighting/PointLight.h>
#include <rendering/lighting/SpotLight.h>

/** Noise **/
#include <math/noise/NoiseMap.h>
#include <math/noise/PerlinNoise.h>

/** Tools **/
#include <editor/tools/ModelViewer.h>

/** UI Windows **/
#include <editor/ui/UITestWindow.h>
#include <editor/ui/UIRenderWindow.h>
#include <editor/ui/MainWindow.h>
#include <editor/ui/UIDataWindow.h>
/******* EXTERNAL LIBRARIES ********/
// STBI
#include <dependencies/include/stb_image.h>

// IMGUI
#include <dependencies/imgui/imgui.h>
#include <dependencies/imgui/imgui_impl_glfw.h>
#include <dependencies/imgui/imgui_impl_opengl3.h>

#endif //GAMEENGINE_LIBS_H
