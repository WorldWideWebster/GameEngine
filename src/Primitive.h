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
#include "vertex.h"

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

        VertTanCalc(vertices, nrOfVertices);

        GLuint indices[] =
        {
                0, 1, 2	//Triangle 1
        };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

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

        VertTanCalc(vertices, nrOfVertices);

        GLuint indices[] =
        {
            0, 1, 2,	//Triangle 1
            0, 2, 3		//Triangle 2
        };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};

class Cube : public Primitive
{
public:
    Cube()
            : Primitive()
    {
        Vertex vertices[] =
        {
             /*   //Position	    				//Normals                       //Texcoords
                {glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 1.f)},
                {glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f)},
                {glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)},
                {glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f)},

                {glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(0.f, 1.f)},
                {glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(0.f, 0.f)},
                {glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(0.f, 0.f, -1.f),		glm::vec2(1.f, 0.f)},
                {glm::vec3(-0.5f, 0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(1.f, 1.f)}
*/

                {glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f)},
                {glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)},
                {glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f)},
                {glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 1.f)},

                {glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(0.f, 0.f, -1.f),		glm::vec2(1.f, 0.f)},
                {glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(0.f, 0.f)},
                {glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(0.f, 1.f)},
                {glm::vec3(-0.5f, 0.5f, -0.5f),		glm::vec3(0.f, 0.f, -1.f),		glm::vec2(1.f, 1.f)}
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        VertTanCalc(vertices, nrOfVertices);

        GLuint indices[] =
        {
                // front
                0, 1, 2,
                2, 3, 0,
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3


                // FIXME: there are not enough indices to draw a cube. I tdepends on the poisiton of the vertices
        };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};
#endif //OPENGLSETUP_PRIMITIVE_H


// reference https://github.com/Headturna/OpenGL-C---Tutorials/blob/master/Primitives.h