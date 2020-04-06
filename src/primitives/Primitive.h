//
// Created by Sean on 3/12/2019.
//

#ifndef OPENGLSETUP_PRIMITIVE_H
#define OPENGLSETUP_PRIMITIVE_H

// STD Library Includes
#include <vector>

// OpenGL includes
#include <glad/glad.h>

// Engine Includes
#include "../vertex.h"

class Primitive
{
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
public:
    Primitive() {};
    virtual ~Primitive() {};

    // Functions
    void set(const Vertex *vertices, const unsigned nrOfVertices, const GLuint *indices, const unsigned nrOfIndices);

    inline std::vector<Vertex> getVertices() { return this->vertices; }
    inline std::vector<GLuint> getIndices()  { return this->indices; }
    inline const unsigned getNrOfVertices() { return this->vertices.size(); }
    inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Triangle : public Primitive
{
public:
    Triangle() : Primitive()
    {
        Vertex vertices[] =
        {
            //Position								//Texcoords					//Normals
            {glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(0.f, 0.f, 1.f),   glm::vec2(0.5f, 1.f)},
            {glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),   glm::vec2(0.f, 0.f)},
            {glm::vec3(0.5f, -0.5f, 0.f),           glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f)}
        };

        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);


        GLuint indices[] =
        {
                0, 1, 2	//Triangle 1
        };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
		ImprovedVertTanCalc(vertices, nrOfVertices, indices, nrOfIndices);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};

class Quad : public Primitive
{
public:
    Quad() : Primitive()
    {
        Vertex vertices[] =
        {
            //Position							//Normals			                //Texcoords
            {glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),			glm::vec2(0.f, 1.f)},
            {glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),			glm::vec2(0.f, 0.f)},
            {glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),			glm::vec2(1.f, 0.f)},
            {glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),			glm::vec2(1.f, 1.f)}
        };

        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);


        GLuint indices[] =
        {
            0, 1, 2,	//Triangle 1
            0, 2, 3		//Triangle 2
        };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
		ImprovedVertTanCalc(vertices, nrOfVertices, indices, nrOfIndices);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};

class Cube : public Primitive
{
public:
    Cube() : Primitive()
    {
        Vertex vertices[] =
        {
             //Position	    				        //Normals                       //Texcoords

            // Front Face
            {glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f)},
            {glm::vec3( 0.5f, -0.5f,  0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)},
            {glm::vec3( 0.5f,  0.5f,  0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f)},
            {glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 1.f)},

            //Back Face
            {glm::vec3(-0.5f, -0.5f, -0.5f),	    glm::vec3(0.f, 0.f, -1.f),		glm::vec2(1.f, 0.f)},
            {glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(1.f, 1.f)},
            {glm::vec3( 0.5f,  0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(0.f, 1.f)},
            {glm::vec3( 0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(0.f, 0.f)},

            // Top Face
            {glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(0.f, 1.f,  0.f),		glm::vec2(0.f, 0.f)},
            {glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec3(0.f, 1.f,  0.f),		glm::vec2(1.f, 0.f)},
            {glm::vec3( 0.5f,  0.5f,  0.5f),		glm::vec3(0.f, 1.f,  0.f),		glm::vec2(1.f, 1.f)},
            {glm::vec3( 0.5f,  0.5f, -0.5f),		glm::vec3(0.f, 1.f,  0.f),		glm::vec2(0.f, 1.f)},

            // Bottom Face
            {glm::vec3(-0.5f, -0.5f, -0.5f),	    glm::vec3(0.f, -1.f, 0.f),		glm::vec2(0.f, 0.f)},
            {glm::vec3( 0.5f, -0.5f, -0.5f),		glm::vec3(0.f, -1.f, 0.f),		glm::vec2(1.f, 0.f)},
            {glm::vec3( 0.5f, -0.5f,  0.5f),		glm::vec3(0.f, -1.f, 0.f),		glm::vec2(1.f, 1.f)},
            {glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec3(0.f, -1.f, 0.f),		glm::vec2(0.f, 1.f)},

            // Right Face
            {glm::vec3( 0.5f, -0.5f, -0.5f),		glm::vec3(1.f, 0.f,  0.f),		glm::vec2(0.f, 0.f)},
            {glm::vec3( 0.5f,  0.5f, -0.5f),		glm::vec3(1.f, 0.f,  0.f),		glm::vec2(0.f, 1.f)},
            {glm::vec3( 0.5f,  0.5f,  0.5f),		glm::vec3(1.f, 0.f,  0.f),		glm::vec2(1.f, 1.f)},
            {glm::vec3( 0.5f, -0.5f,  0.5f),		glm::vec3(1.f, 0.f,  0.f),		glm::vec2(1.f, 0.f)},

            // Left Face
            {glm::vec3(-0.5f, -0.5f, -0.5f),	    glm::vec3(-1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f)},
            {glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec3(-1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f)},
            {glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec3(-1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f)},
            {glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(-1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f)}
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] =
        {
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23    // left
        };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
		ImprovedVertTanCalc(vertices, nrOfVertices, indices, nrOfIndices);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};
Cube *getUnitCube(void);

#endif //OPENGLSETUP_PRIMITIVE_H


// reference https://github.com/Headturna/OpenGL-C---Tutorials/blob/master/Primitives.h