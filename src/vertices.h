//
// Created by Sean on 11/15/2018.
//

#ifndef VERTICES_H
#define VERTICES_H

#include <vector>


float planeVertices[] = {
        // positions          // texture Coords
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

// transparent vegetation locations
// --------------------------------
std::vector<glm::vec3> vegetation
        {
                glm::vec3(-1.5f, 0.0f, -0.48f),
                glm::vec3( 1.5f, 0.0f, 0.51f),
                glm::vec3( 0.0f, 0.0f, 0.7f),
                glm::vec3(-0.3f, 0.0f, -2.3f),
                glm::vec3 (0.5f, 0.0f, -0.6f)
        };
std::vector<glm::vec3> windows
        {
                glm::vec3(-1.5f, 0.0f, -0.48f),
                glm::vec3( 1.5f, 0.0f, 0.51f),
                glm::vec3( 0.0f, 0.0f, 0.7f),
                glm::vec3(-0.3f, 0.0f, -2.3f),
                glm::vec3( 0.5f, 0.0f, -0.6f)
        };


// positions of the point lights
glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
};

std::vector<std::string> faces
{
        ("../resources/textures/skybox/right.jpg"),
        ("../resources/textures/skybox/left.jpg"),
        ("../resources/textures/skybox/top.jpg"),
        ("../resources/textures/skybox/bottom.jpg"),
        ("../resources/textures/skybox/front.jpg"),
        ("../resources/textures/skybox/back.jpg")
};
/*
std::vector<std::string> faces
{
        ("../resources/textures/ame_nebula/purplenebula_rt.tga"),
        ("../resources/textures/ame_nebula/purplenebula_lf.tga"),
        ("../resources/textures/ame_nebula/purplenebula_up.tga"),
        ("../resources/textures/ame_nebula/purplenebula_dn.tga"),
        ("../resources/textures/ame_nebula/purplenebula_ft.tga"),
        ("../resources/textures/ame_nebula/purplenebula_bk.tga")
};
*/
#endif //VERTICES_H
