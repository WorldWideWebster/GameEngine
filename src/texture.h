//
// Created by Sean on 11/17/2018.
//

#ifndef TEXTURE_H
#define TEXTURE_H


#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>


struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

unsigned int loadTexture(char const * path);
unsigned int loadCubemap(std::vector<std::string> faces);

unsigned char *loadHeightMap(char const * path, int *width, int *height);


#endif //TEXTURE_H
