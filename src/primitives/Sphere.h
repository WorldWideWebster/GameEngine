//
// Created by Sean on 5/21/2019.
//

// used http://www.songho.ca/opengl/gl_sphere.html as a basis


#ifndef OPENGLSETUP_SPHERE_H
#define OPENGLSETUP_SPHERE_H

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


#endif //OPENGLSETUP_SPHERE_H
