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

// TODO: add width/height to struct
/*
 * Return the id of the texture, use the struct when loading from file
 * create generic image loader -> texture, heightmap etc?
 * create loaded texture list
 */

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
    int width;
    int height;
    int nrComponents;
};

unsigned int loadTexture(char const * path);
unsigned int loadCubemap(std::vector<std::string> faces);

unsigned char **loadXYHeightMap(char const * path, int *width, int *height);


#endif //TEXTURE_H
