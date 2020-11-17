set(SOURCE_FILES
        main.cpp
        rendering/camera.cpp
        rendering/mesh.cpp
        rendering/model.cpp
        )
set(HEADER_FILES
        stb_image.h
        rendering/camera.h
        rendering/mesh.h
        rendering/model.h
        )

include_directories(${BULLET_ROOT_DIR})

add_subdirectory(imgui)
add_subdirectory(primitives)
add_subdirectory(noise)
add_subdirectory(image)
add_subdirectory(lighting)
add_subdirectory(shader)
add_subdirectory(buffer-objects)
add_subdirectory(rendering)
add_subdirectory(ui)
add_subdirectory(tools)
