set(SOURCE_FILES
        main.cpp
        shader.cpp
        camera.cpp
        mesh.cpp
        model.cpp
        )
set(HEADER_FILES
        shader.h
        stb_image.h
        camera.h
        mesh.h
        model.h)


add_subdirectory(imgui)
add_subdirectory(primitives)
add_subdirectory(noise)
add_subdirectory(image)

