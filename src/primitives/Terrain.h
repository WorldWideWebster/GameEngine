//
// Created by Sean on 4/8/2019.
//

#ifndef GAMEENGINE_TERRAIN_H
#define GAMEENGINE_TERRAIN_H

// STD Library Includes
#include <vector>

// OpenGL includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Engine Includes
#include "vertex.h"
#include "Primitive.h"
#include "image/texture.h"
#include "image/HeightMap.h"



class Terrain : public Primitive
{
public:
	/**
	 * @brief Terrain default constructor. Generates terrain using random perlin noise
	 */
    Terrain();
    /**
     * @brief Terrain constructor. Generates terrain using heightmap file
     * @param heightMapFile string path to file to use as heightmap
     */
	Terrain(std::string heightMapFile);
	/**
	 * @brief generates vertices for terrain
	 * @return vertices generate
	 */
	Vertex *generateVertices(void);
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


#endif //GAMEENGINE_TERRAIN_H
