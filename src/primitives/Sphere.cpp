//
// Created by Sean on 5/21/2019.
//

#include "Sphere.h"
// Default Constructor
Sphere::Sphere() : Primitive()
{
    sectorCount = 10; // latitudinal sectors
    stackCount = 10;  // vertical stacks
    radius = 1.0f;

    std::vector<Vertex> vertices = calcVertices();
    unsigned nrOfVertices = vertices.size();

    // generate CCW index list of sphere triangles
    std::vector<GLuint> indices = calcIndices();
    unsigned nrOfIndices = indices.size();
	ImprovedVertTanCalc(vertices.data(), nrOfVertices, indices.data(), nrOfIndices);

    this->set(vertices.data(), nrOfVertices, indices.data(), nrOfIndices);
}

Sphere::Sphere(int secCount, int staCount, float rad) : Primitive()
{
    sectorCount = secCount; // latitudinal sectors
    stackCount = staCount;  // vertical stacks
    radius = rad;

    std::vector<Vertex> vertices = calcVertices();
    unsigned nrOfVertices = vertices.size();

    // generate CCW index list of sphere triangles
    std::vector<GLuint> indices = calcIndices();
    unsigned nrOfIndices = indices.size();
	ImprovedVertTanCalc(vertices.data(), nrOfVertices, indices.data(), nrOfIndices);

    this->set(vertices.data(), nrOfVertices, indices.data(), nrOfIndices);
}

std::vector<Vertex> Sphere::calcVertices()
{
    const float PI = 3.1415926f;

    float x, y, z, xy;                              // vertex position

    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    std::vector<Vertex> vertices;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            glm::vec3 position = glm::vec3(x, y, z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            glm::vec3 normals = glm::vec3(nx, ny, nz);


            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            glm::vec2 texcoords = glm::vec2(s, t);
            vertices.push_back((Vertex){position, normals, texcoords});
        }
    }
    return vertices;
}


std::vector<GLuint> Sphere::calcIndices()
{
    // generate CCW index list of sphere triangles
    std::vector<GLuint> indices;
    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stackCount-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    return indices;
}
