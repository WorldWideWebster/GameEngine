//
// Created by Sean on 4/8/2019.
//

#include "Terrain.h"
#include "../vertex.h"

#include "../stb_image.h"
#include <string>




// TODO: Terrain contains a heightmap, generated off of noisemap

// Default Terrain constructor
Terrain::Terrain() : Primitive()
{
    // Default terrain generation values
    scale = 0.5;
    size = 512*4;

//    std::string filename = "../resources/heightmap.png";

//    setImageAsHeightMap(filename);

	NoiseMap nm;
    setArrayAsHeightMap(nm.getData(), nm.getHeight(), nm.getWidth());


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

    calculateNormals(heightMap, vertices);
    GLuint *indices = new GLuint[6*(vertex_count-1)*(vertex_count-1)];
    calculateIndices(indices, width, height);

//
//	for(unsigned int i = 0; i < (width -1) * (height-1); i = i+3){
//
//		glm::vec3 vertex0 = vertices[indices[i]].Position;
//		glm::vec3 vertex1 = vertices[indices[i + 1]].Position;
//		glm::vec3 vertex2 = vertices[indices[i + 2]].Position;
//
//		glm::vec3 normal = glm::cross((vertex1 - vertex0),(vertex2 - vertex0));
//
//		glm::vec3 deltaPos;
//		if(vertex0 == vertex1)
//			deltaPos = vertex2 - vertex0;
//		else
//			deltaPos = vertex1 - vertex0;
//
//		glm::vec2 uv0 = vertices[indices[i]].TexCoords;
//		glm::vec2 uv1 = vertices[indices[i + 1]].TexCoords;
//		glm::vec2 uv2 = vertices[indices[i + 2]].TexCoords;
//
//		glm::vec2 deltaUV1 = uv1 - uv0;
//		glm::vec2 deltaUV2 = uv2 - uv0;
//
//		glm::vec3 tan; // tangents
//		glm::vec3 bit; // bitangent
//
//		// avoid divion with 0
//		if(deltaUV1.s != 0)
//			tan = deltaPos / deltaUV1.s;
//		else
//			tan = deltaPos / 1.0f;
//
//		tan = glm::normalize(tan - glm::dot(normal,tan)*normal);
//
//		bit = glm::normalize(glm::cross(tan, normal));
//
//		// write into array - for each vertex of the face the same value
//		vertices[indices[i]].Tangent = tan;
//		vertices[indices[i + 1]].Tangent = tan;
//		vertices[indices[i + 2]].Tangent = tan;
//
//		vertices[indices[i]].Bitangent = bit;
//		vertices[indices[i + 1]].Bitangent = bit;
//		vertices[indices[i + 2]].Bitangent = bit;
//	}
    unsigned nrOfVertices = (vertex_count)*(vertex_count);

    VertTanCalc(vertices, nrOfVertices);

    unsigned nrOfIndices = 6*(vertex_count-1)*(vertex_count-1);

    this->set(vertices, nrOfVertices, indices, nrOfIndices);
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
            vertexPointer++;
        }
    }
}

void Terrain::calculateBTs(GLuint *indices, Vertex *vertices)
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