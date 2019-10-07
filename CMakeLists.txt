cmake_minimum_required(VERSION 3.7)
project(OpenGLSetup)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        GLAD/src/glad.c)
set(HEADER_FILES
        src/shader.cpp
        src/shader.h
        src/stb_image.h
        src/camera.cpp
        src/camera.h
        src/mesh.cpp
        src/mesh.h
        src/model.cpp
        src/model.h
        src/window.cpp
        src/window.h
        src/vertices.h
        src/vertex.h
        src/vertex.cpp
        src/texture.cpp
        src/texture.h
        src/engine.cpp
        src/engine.h
        src/renderutil.cpp
        src/renderutil.h
        src/shape.cpp
        src/shape.h
        src/main_defs.h
        src/libs.h
        src/Lighting.cpp
        src/Lighting.h
        src/RenderBuffer.cpp
        src/RenderBuffer.h
        src/image/Image.cpp
        src/image/Image.h
        src/tools/ImageViewer.cpp
        src/tools/ImageViewer.h
        src/Entity.cpp
        src/Entity.h
        src/Scene.cpp
        src/Scene.h
        src/Environment.cpp
        src/Environment.h
        src/Renderer.cpp src/Renderer.h src/ui/UIWindow.cpp src/ui/UIWindow.h src/ui/UIRenderWindow.cpp src/ui/UIRenderWindow.h src/ui/UITestWindow.cpp src/ui/UITestWindow.h)

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

#Copy libs to build folder
add_custom_command(TARGET OpenGLSetup PRE_BUILD         # Adds a post-build event to OpenGLSetup
        COMMAND ${CMAKE_COMMAND} -E copy_directory      # which executes "cmake - E copy_directory..."
        "${PROJECT_SOURCE_DIR}/dependencies/libs"       # <--this is in-file
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})              # <--this is out-file path

#Copy resources folder to build folder
add_custom_command(TARGET OpenGLSetup PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources"
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

#FIXME: There must be a better way to add the assimp library
target_link_libraries(OpenGLSetup glfw noise primitives lighting imgui ${dir}/dependencies/libs/libassimpd.dll.a)
