
set(engine_source_files
        Entity.cpp
        Scene.cpp
        Environment.cpp
        engine.cpp
        )

set(engine_header_files
        Entity.h
        Scene.h
        Environment.h
        engine.h
        )


add_library(engine ${engine_source_files} ${engine_header_files})