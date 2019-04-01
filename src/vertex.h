//
// Created by Sean on 11/16/2018.
//

#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;

    Vertex(){}
    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
    {
        this->Position = pos;
        this->Normal = norm;
        this->TexCoords = tex;
    }
};

std::vector<Vertex> vertexFromVertices(std::vector<float> vertexIn);

std::vector<Vertex> fillVertexVector(std::vector<float> verticesIn, std::vector<float> normsIn, std::vector<float> texcIn);
void VertTanCalc(Vertex *verticesIn, GLuint nrOfVertices);

#endif //VERTEX_H
