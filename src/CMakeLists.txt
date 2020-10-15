set(SOURCE_FILES
        main.cpp
        camera.cpp
        mesh.cpp
        model.cpp
        Renderer.cpp
        )
set(HEADER_FILES
        stb_image.h
        camera.h
        mesh.h
        model.h
        Renderer.h)


add_subdirectory(imgui)
add_subdirectory(primitives)
add_subdirectory(noise)
add_subdirectory(image)
add_subdirectory(lighting)
add_subdirectory(shader)
add_subdirectory(ui)
add_subdirectory(buffer-objects)
add_subdirectory(tools)
add_subdirectory(rendering)


