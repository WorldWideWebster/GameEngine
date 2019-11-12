set(SOURCE_FILES
        main.cpp
        camera.cpp
        mesh.cpp
        model.cpp
        )
set(HEADER_FILES
        stb_image.h
        camera.h
        mesh.h
        model.h)


add_subdirectory(imgui)
add_subdirectory(primitives)
add_subdirectory(noise)
add_subdirectory(image)
add_subdirectory(lighting)
add_subdirectory(shader)
add_subdirectory(ui)

