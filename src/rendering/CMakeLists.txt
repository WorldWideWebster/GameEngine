set(rendering_source_files
        renderutil.cpp
        Lighting.cpp
        mesh.cpp
        model.cpp
        camera.cpp
        Renderer.cpp
        )

set(rendering_header_files
        renderutil.h
        Lighting.h
        mesh.h
        model.h
        camera.h
        Renderer.h
        )

add_subdirectory(buffer-objects)
add_subdirectory(primitives)
add_subdirectory(shader)
add_subdirectory(lighting)
add_subdirectory(image)


add_library(rendering ${rendering_header_files} ${rendering_source_files})