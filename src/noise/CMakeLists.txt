set(noise_source_files
        Noise.cpp
        PerlinNoise.cpp
        PerlinNoise.h
        Noise.h
        NoiseMap.cpp
        NoiseMap.h)

add_library(noise ${noise_source_files})