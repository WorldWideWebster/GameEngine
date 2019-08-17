set(primitives_source_files
        Primitive.cpp
        Primitive.h
        Terrain.cpp
        Terrain.h Sphere.cpp Sphere.h SkyBox.cpp SkyBox.h)

add_library(primitives ${primitives_source_files})