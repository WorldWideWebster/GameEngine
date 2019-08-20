//
// Created by Sean on 4/8/2019.
//

#ifndef OPENGLSETUP_TERRAIN_H
#define OPENGLSETUP_TERRAIN_H

// STD Library Includes
#include <vector>

// OpenGL includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Engine Includes
#include "../vertex.h"
#include "Primitive.h"
#include "../texture.h"
#include "../HeightMap.h"



class Terrain : public Primitive
{
public:
    Terrain();

    virtual ~Terrain();
    void calculateNormals(std::vector< std::vector<unsigned char>> heightMap, Vertex *vertices);
    void calculateIndices(GLuint *indices, int width, int height);
    void setImageAsHeightMap(std::string filename);
    void setArrayAsHeightMap(unsigned char *data, int width, int height);
    void setHeightMap(unsigned char *data, int width, int height);
private:
    std::vector< std::vector<unsigned char>> heightMap;
    int nrComponents;
    GLuint size;
    GLuint vertex_count;
    float x, y;
    float scale = 1;
   // HeightMap heightMap;
    int width, height;
};


#endif //OPENGLSETUP_TERRAIN_H
