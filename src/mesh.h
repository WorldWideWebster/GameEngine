//
// Created by Sean on 10/18/2018.
//

#ifndef OPENGLSETUP_MESH_H
#define OPENGLSETUP_MESH_H

// STD Library Includes
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Engine Includes
#include "texture.h"
#include "primitives/Primitive.h"
#include "shader/shader.h"
#include "vertex.h"


class Mesh {
public:
    /* Mesh Data */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /* Functions */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(Primitive *primitive);
    Mesh(Primitive *primitive, std::vector <Texture> textures);
    Mesh(Primitive *primitive, Texture texture);
    ~Mesh()
    {
        vertices.clear();
        indices.clear();
        textures.clear();
    }
	// WHY: can I not make draw virtual?
    void Draw(Shader shader);
    unsigned int getVAO(void);
    unsigned int getDefaultTexture(void);
private:
    /* Render Data */
    unsigned int VAO, VBO, EBO;
    /* Functions */
    void setupMesh();
    GLuint DEFAULT_TEXTURE;
    bool didShadows = false;
};


#endif //OPENGLSETUP_MESH_H
