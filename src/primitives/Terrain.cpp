//
// Created by Sean on 4/8/2019.
//

#include "Terrain.h"
#include "../vertex.h"

#include "../stb_image.h"

#include <string>



// Default Terrain constructor
Terrain::Terrain() : Primitive()
{
    // Default terrain generation values
    scale = 0.25;
    size = 512;

    std::string filename = "../resources/heightmap.png";

    setImageAsHeightMap(filename);


    vertex_count = height;
    int count = vertex_count * vertex_count;
    Vertex *vertices = new Vertex[count];
    int vertexPointer = 0;
    for(int gy=0;gy<vertex_count;gy++)
    {
        for(int gx=0;gx<vertex_count;gx++)
        {
            // Fill vertices
            vertices[vertexPointer] =
                    {glm::vec3(((float)gx/((float)vertex_count - 1) * size), (float)heightMap[gy][gx]*scale, ((float)gy/((float)vertex_count - 1) * size)),
                     glm::vec3(0, 1, 0),
                     glm::vec2((float)gx/((float)vertex_count - 1), (float)gy/((float)vertex_count - 1))};
            vertexPointer++;
        }
    }

    calculateNormals(heightMap, vertices);
    GLuint *indices = new GLuint[6*(vertex_count-1)*(vertex_count-1)];
    calculateIndices(indices, width, height);

    unsigned nrOfVertices = (vertex_count)*(vertex_count);

    VertTanCalc(vertices, nrOfVertices);

    unsigned nrOfIndices = 6*(vertex_count-1)*(vertex_count-1);

    this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Terrain::~Terrain()
{
}

// FIXME: Normal x-y directions are backwards?
// Switch D-U/ L-R?
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
            float heightU = heightMap[gy ? gy - 1 : gy][gx];
            float heightD = heightMap[gy < vertex_count-1 ? gy + 1 : gy][gx];
            glm::vec3 norm = glm::vec3((heightL - heightR), 2.0f, heightU - heightD);
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

void Terrain::setImageAsHeightMap(std::string filename)
{
    // Load heightmap
    stbi_uc *image = stbi_load(filename.c_str(), &width, &height, &nrComponents, 1);
    if (image)
        std::clog << "Read \"" << filename << "\": " << width << "x" << height << "x" << nrComponents << std::endl;
    else
        std::clog << stbi_failure_reason() << std::endl;



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

    stbi_image_free(image);
}