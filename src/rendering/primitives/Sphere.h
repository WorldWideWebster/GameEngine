//
// Created by Sean on 5/21/2019.
//

// used http://www.songho.ca/opengl/gl_sphere.html as a basis


#ifndef GAMEENGINE_SPHERE_H
#define GAMEENGINE_SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive
{
public:
    Sphere();
    Sphere(int secCount, int staCount, float rad);


private:
    int sectorCount;
    int stackCount;
    float radius;

    std::vector<Vertex> calcVertices();
    std::vector<GLuint> calcIndices();

};


#endif //GAMEENGINE_SPHERE_H
