cmake_minimum_required(VERSION 3.7)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

#Allow program to run standalone in windows
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(SOURCE_FILES
        src/main.cpp
        GLAD/src/glad.c)
set(HEADER_FILES
        dependencies/include/stb_image.h
        src/common/window.cpp
        src/common/window.h
        src/common/main_defs.h
        src/common/libs.h
        src/common/test_scenes.h
        src/common/test_scenes.cpp
        )

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

include_directories(dependencies/include)
include_directories(dependencies/GLFW/include)

#Include library files
include_directories(GLAD/include)
include_directories(glm/include)
include_directories(src)
include_directories(dependencies/include)
include_directories(bullet3/src)
include_directories(${dir})


file(COPY resources DESTINATION ${dir}/build)
file(COPY shaders DESTINATION ${dir}/build)


#Add deps
add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(bullet3)

set(BULLET_ROOT ${dir}/bullet3/build) # where to find Bullet
set(BULLET_INCLUDE_DIR ${dir}/bullet3/src) # where to find Bullet
set(BULLET_PHYSICS_SOURCE_DIR ${dir}/bullet3) # where to find Bullet
find_package(BULLET REQUIRED) # find Bullet and fill environment variables


add_executable(GameEngine ${SOURCE_FILES} ${HEADER_FILES})

#Copy libs to build folder
add_custom_command(TARGET GameEngine PRE_BUILD         # Adds a post-build event to GameEngine
        COMMAND ${CMAKE_COMMAND} -E copy_directory      # which executes "cmake - E copy_directory..."
        "${PROJECT_SOURCE_DIR}/dependencies/libs"       # <--this is in-file
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})              # <--this is out-file path

#Copy resources folder to build folder
add_custom_command(TARGET GameEngine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources"
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

#FIXME: There must be a better way to add the assimp library
target_link_libraries(
        GameEngine
        engine
        image
        rendering
        glfw
        buffer_objects
        noise
        primitives
        lighting
        imgui
        shader
        ui
        tools
        ${dir}/dependencies/libs/libassimpd.dll.a
        ${BULLET_DYNAMICS_LIBRARY}
        ${BULLET_COLLISION_LIBRARY}
        ${BULLET_MATH_LIBRARY})

