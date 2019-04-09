cmake_minimum_required(VERSION 3.7)
project(OpenGLSetup)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp GLAD/src/glad.c)
set(HEADER_FILES src/shader.cpp src/shader.h src/stb_image.h src/camera.cpp src/camera.h src/mesh.cpp src/mesh.h src/model.cpp src/model.h src/window.cpp src/window.h src/vertices.h src/CubeStuff.cpp src/vertex.h src/vertex.cpp src/texture.cpp src/texture.h src/engine.cpp src/engine.h src/renderutil.cpp src/renderutil.h src/shape.cpp src/shape.h src/primitivesolid.cpp src/primitivesolid.h src/cube.cpp src/cube.h src/Light.cpp src/Light.h src/main_defs.h src/libs.h src/Terrain.cpp src/Terrain.h)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

include_directories(dependencies/include)

#Include library files
include_directories(GLAD/include)
include_directories(glm/include)

file(COPY resources DESTINATION ${dir}/build)
file(COPY shaders DESTINATION ${dir}/build)


#Add deps
add_subdirectory(dependencies)
add_subdirectory(src)


add_executable(OpenGLSetup ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(OpenGLSetup glfw imgui ${dir}/build/libassimpd.dll.a)
