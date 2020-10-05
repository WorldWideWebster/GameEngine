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
    scale = 0.5;
    size = 512*4;

	NoiseMap nm;
    setArrayAsHeightMap(nm.getData(), nm.getHeight(), nm.getWidth());

	Vertex *vertices = generateVertices();

    calculateNormals(heightMap, vertices);
	GLuint *indices = new GLuint[6*(height-1)*(width-1)];
	calculateIndices(indices, width, height);
	unsigned nrOfIndices = 6*(height-1)*(width-1);
	unsigned nrOfVertices = (height)*(width);
	ImprovedVertTanCalc(vertices, nrOfVertices, indices, nrOfIndices);


    this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Terrain::Terrain(std::string heightMapFile)
{
	setImageAsHeightMap(heightMapFile);

	Vertex *vertices = generateVertices();
	calculateNormals(heightMap, vertices);
	GLuint *indices = new GLuint[6*(height-1)*(width-1)];
	calculateIndices(indices, width, height);
	unsigned nrOfIndices = 6*(height-1)*(width-1);
	unsigned nrOfVertices = (height)*(width);
	ImprovedVertTanCalc(vertices, nrOfVertices, indices, nrOfIndices);


	this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Vertex* Terrain::generateVertices(void)
{
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
					 glm::vec2(gx, gy)};
			vertexPointer++;
		}
	}
	return vertices;
}

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
            glm::vec3 norm = glm::vec3((heightL - heightR), 1.0f, heightU - heightD);
            norm = glm::normalize(norm);
            vertices[vertexPointer].Normal = norm;

			const glm::vec3 rightVec = glm::vec3(1.0, 0.0, 0.0);
			glm::vec3 N = norm;
			glm::vec3 T = cross(rightVec, N);
			glm::vec3 B = cross(T, N);
			vertices[vertexPointer].Tangent = T;
			vertices[vertexPointer].Bitangent = B;
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

void Terrain::setArrayAsHeightMap(unsigned char *data, int width, int height)
{
	this->width = width;
	this->height = height;
	this->nrComponents = 3;
	heightMap.clear();
    if (data)
    {
		// Move array pointer by 3 each time to only use one color in each pixel
        for(int gy = 0; gy < height * 3; gy+=3)
        {
            std::vector<unsigned char> heightMapRow;
            for(int gx = 0; gx < width * 3; gx+=3)
            {
                heightMapRow.push_back(data[width * gy + gx]);
            }
            heightMap.push_back(heightMapRow);
        }
    }
}

void Terrain::setHeightMap(unsigned char *data, int width, int height)
{
	//TODO: clear previous heightmap data
	setArrayAsHeightMap(data, width, height);

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
