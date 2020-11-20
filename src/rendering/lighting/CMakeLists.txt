set(lighting_source_files
        Light.cpp
        Light.h
        PointLight.cpp
        PointLight.h
        DirectionalLight.cpp
        DirectionalLight.h
        SpotLight.cpp
        SpotLight.h
        )

add_library(lighting ${lighting_source_files})