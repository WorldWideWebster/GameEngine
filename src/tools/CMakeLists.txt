set(tools_source_files
        Tool.cpp
        ModelViewer.cpp
        NoiseMapViewer.cpp

        )

set(tools_header_files
        Tool.h
        ModelViewer.h
        NoiseMapViewer.h

        )

add_library(tools ${tools_source_files} ${tools_header_files})