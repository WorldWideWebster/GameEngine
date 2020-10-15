set(primitives_source_files
        vertex.cpp
        Primitive.cpp
        Terrain.cpp
        Sphere.cpp
        SkyBox.cpp
        shape.cpp
        )

set(primitives_header_files
        vertex.h
        Primitive.h
        Terrain.h
        Sphere.h
        SkyBox.h
        shape.h
        vertices.h
        )

add_library(primitives ${primitives_header_files} ${primitives_source_files})