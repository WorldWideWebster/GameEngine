//
// Created by Sean on 3/12/2019.
//

#include "Primitive.h"

void Primitive::set(const Vertex *vertices, const unsigned nrOfVertices, const GLuint *indices, const unsigned nrOfIndices)
{
    for (size_t i = 0; i <nrOfVertices; i++)
    {
        this->vertices.push_back(vertices[i]);
    }

    for (size_t i = 0; i < nrOfIndices; i++)
    {
        this->indices.push_back(indices[i]);
    }
}