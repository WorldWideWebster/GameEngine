//
// Created by Sean on 4/8/2019.
//

#ifndef OPENGLSETUP_TERRAIN_H
#define OPENGLSETUP_TERRAIN_H

// STD Library Includes
#include <vector>

// OpenGL includes
#include <glad/glad.h>

// Engine Includes
#include "vertex.h"
#include "Primitive.h"


class Terrain : public Primitive
{
public:
    Terrain() : Primitive()
    {
        size = 200;
        vertex_count = 32;
        int count = vertex_count * vertex_count;
        Vertex vertices[count];
        GLuint indices[6*(vertex_count-1)*(vertex_count-1)];
        int vertexPointer = 0;
        for(int i=0;i<vertex_count;i++){
            for(int j=0;j<vertex_count;j++){
                vertices[vertexPointer] =
                        {glm::vec3(((float)j/((float)vertex_count - 1) * size), 0, ((float)i/((float)vertex_count - 1) * size)),
                        glm::vec3(0, 1, 0),
                        glm::vec2((float)j/((float)vertex_count - 1), (float)i/((float)vertex_count - 1))};
                vertexPointer++;
            }
        }
        int pointer = 0;
        for(int gz=0;gz<vertex_count-1;gz++){
            for(int gx=0;gx<vertex_count-1;gx++){
                int topLeft = (gz*vertex_count)+gx;
                int topRight = topLeft + 1;
                int bottomLeft = ((gz+1)*vertex_count)+gx;
                int bottomRight = bottomLeft + 1;
                indices[pointer++] = topLeft;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = topRight;
                indices[pointer++] = topRight;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = bottomRight;
            }
        }

        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        VertTanCalc(vertices, nrOfVertices);

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }

private:
    GLuint size;
    GLuint vertex_count;
    float x, y;

};


#endif //OPENGLSETUP_TERRAIN_H
