//
// Created by Sean on 4/8/2019.
//

#include "Terrain.h"

#include "../stb_image.h"

// Default Terrain constructor
Terrain::Terrain() : Primitive()
{
    // Default terrain generation values
    scale = 1;
    size = 512;

    int nrComponents;
    // TODO: move heightmap loading to separate function
    stbi_uc *image = stbi_load("../resources/heightmap.png", &width, &height, &nrComponents, 1);
    std::vector< std::vector<unsigned char>> heightMap;
    if (image)
    {
        for(int gy = 0; gy < height; gy++)
        {
            std::vector<unsigned char> heightMapRow;
            for(int gx = 0; gx < width; gx++)
            {
                heightMapRow.push_back(image[width * gy + gx]);
            }
            heightMap.push_back(heightMapRow);
        }
    }

    vertex_count = height;
    int count = vertex_count * vertex_count;
    // FIXME: fix stack overflow on larger heightmaps
    Vertex vertices[count];
    int vertexPointer = 0;
    for(int gy=0;gy<vertex_count;gy++)
    {
        for(int gx=0;gx<vertex_count;gx++)
        {
            // Fill vertices
            vertices[vertexPointer] =
                    {glm::vec3(((float)gx/((float)vertex_count - 1) * size), (float)heightMap[gy][gx]/scale, ((float)gy/((float)vertex_count - 1) * size)),
                     glm::vec3(0, 1, 0),
                     glm::vec2((float)gx/((float)vertex_count - 1), (float)gy/((float)vertex_count - 1))};
            vertexPointer++;
        }
    }

    // Generate Normals
    vertexPointer = 0;
    for(int gy=0;gy<vertex_count;gy++)
    {
        for (int gx = 0; gx < vertex_count; gx++)
        {
            float heightL = heightMap[gy][gx ? gx - 1 : gx];
            float heightR = heightMap[gy][gx < vertex_count-1 ? gx + 1 : gx];
            float heightD = heightMap[gy ? gy - 1 : gy][gx];
            float heightU = heightMap[gy < vertex_count-1 ? gy + 1 : gy][gx];
            glm::vec3 norm = glm::vec3((heightR - heightL), 2.0f,heightU - heightD );
            norm = glm::normalize(norm);
            vertices[vertexPointer].Normal = norm;
            vertexPointer++;
        }
    }

     calculateNormals(heightMap, vertices);

    GLuint indices[6*(vertex_count-1)*(vertex_count-1)];
    calculateIndices(indices, width, height);

    unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

    VertTanCalc(vertices, nrOfVertices);

    unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

    this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Terrain::~Terrain()
{

}

// FIXME: function causes crash
void Terrain::calculateNormals(std::vector< std::vector<unsigned char>> heightMap, Vertex *vertices)
{
    // Generate Normals
    int vertexPointer = 0;
    for(int gy=0;gy<vertex_count;gy++)
    {
        for (int gx = 0; gx < vertex_count; gx++)
        {
            float heightL = heightMap[gy][gx ? gx - 1 : gx];
            float heightR = heightMap[gy][gx < vertex_count-1 ? gx + 1 : gx];
            float heightD = heightMap[gy ? gy - 1 : gy][gx];
            float heightU = heightMap[gy < vertex_count-1 ? gy + 1 : gy][gx];
            glm::vec3 norm = glm::vec3((heightR - heightL), 2.0f,heightU - heightD );
            norm = glm::normalize(norm);
            vertices[vertexPointer].Normal = norm;
            vertexPointer++;
        }
    }
}

void Terrain::calculateIndices(GLuint *indices, int width, int height)
{
    // Only squares for now
    // TODO: allow rectangles
    vertex_count = height;
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
}
