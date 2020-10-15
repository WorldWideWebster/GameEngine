set(image_source_files
        Image.cpp
        HeightMap.cpp
        texture.cpp
        )

set(image_header_files
        Image.h
        HeightMap.h
        texture.h
        )

add_library(image ${image_header_files} ${image_source_files})