//
// Created by Sean on 4/8/2019.
//

#include "Terrain.h"

#include "stb_image.h"


Terrain::Terrain() : Primitive()
{
    int width, height;
    int nrComponents;
    // TODO: move heightmap loading to separate function
    stbi_uc *image = stbi_load("../resources/heightmap.png", &width, &height, &nrComponents, 1);
    unsigned char heightMap[height][width];
    if (image)
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                heightMap[i][j] = image[width * i + j];;
            }
        }
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {

            }
        }
    }

    width -= 1;
    height -= 1;
    size = 512;
    vertex_count = height;
    int count = vertex_count * vertex_count;
    // FIXME: fix stack overflow on larger heitmaps
    Vertex vertices[count];
    GLuint indices[6*(vertex_count-1)*(vertex_count-1)];
    int vertexPointer = 0;
    for(int i=0;i<vertex_count;i++)
    {
        for(int j=0;j<vertex_count;j++)
        {
            // Generate Normals
            // FIXME: normals are not generated properly
            glm::vec3 norm = glm::vec3(0, 1, 0);
            if (i != 0 && j != 0 && i != height-1 && j != width-1)
            {
                float heightL = heightMap[j - 1][i];
                float heightR = heightMap[j + 1][i];
                float heightD = heightMap[j][i - 1];
                float heightU = heightMap[j][i + 1];
                norm = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
                norm = glm::normalize(norm);
            }

            // Fill vertices
            vertices[vertexPointer] =
                    {glm::vec3(((float)j/((float)vertex_count - 1) * size), (float)heightMap[i][j]/16, ((float)i/((float)vertex_count - 1) * size)),
                     norm,
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

Terrain::~Terrain()
{

}
