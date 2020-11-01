set(tools_source_files
        Tool.cpp
        ModelViewer.cpp
        NoiseMapViewer.cpp
        TextureViewer.cpp
        )

set(tools_header_files
        Tool.h
        ModelViewer.h
        NoiseMapViewer.h
        TextureViewer.h)

add_library(tools ${tools_source_files} ${tools_header_files})