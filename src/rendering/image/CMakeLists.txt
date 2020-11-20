set(image_source_files
        Image.cpp
        HeightMap.cpp
        texture.cpp
        TextureLibrary.cpp
        CubeMap.cpp
        )

set(image_header_files
        Image.h
        HeightMap.h
        texture.h
        TextureLibrary.h
        CubeMap.h
        )

add_library(image ${image_header_files} ${image_source_files}  )