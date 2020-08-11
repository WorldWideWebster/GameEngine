set(buffer_objects_source_files
        FrameBuffer.cpp
        FrameBuffer.h
        BufferObject.cpp
        BufferObject.h
        ShadowDepthBuffer.cpp
        ShadowDepthBuffer.h
        ShadowCubeDepthBuffer.cpp
        ShadowCubeDepthBuffer.h
        gBuffer.cpp
        gBuffer.h
        )

add_library(buffer_objects ${buffer_objects_source_files})