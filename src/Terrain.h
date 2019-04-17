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
#include "vertex.h"
#include "Primitive.h"
#include "texture.h"



class Terrain : public Primitive
{
public:
    Terrain();

    virtual ~Terrain();

private:
    GLuint size;
    GLuint vertex_count;
    float x, y;

};


#endif //OPENGLSETUP_TERRAIN_H
