//
// Created by Sean on 10/18/2018.
//

#ifndef OPENGLSETUP_MESH_H
#define OPENGLSETUP_MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "vertex.h"
#include "texture.h"

class Mesh {
public:
    /* Mesh Data */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /* Functions */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Draw(Shader shader);
    unsigned int getVAO(void);
private:
    /* Render Data */
    unsigned int VAO, VBO, EBO;
    /* Functions */
    void setupMesh();
};


#endif //OPENGLSETUP_MESH_H
