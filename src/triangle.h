//
// Created by Sean on 12/14/2018.
//

#ifndef OPENGLSETUP_TRIANGLE_H
#define OPENGLSETUP_TRIANGLE_H

#include <vector>
#include "mesh.h"


const float TriangleVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f
};

const std::vector<float> VectorTriangleVertices = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
};
const std::vector<unsigned int> TriangleIndices = {
        // front
        0, 1, 2
};
/*
const std::vector<Vertex> TriangleVertex =  vertexFromVertices(VectorTriangleVertices);


class Triangle : public Mesh
{
public:
    Triangle() : Mesh(TriangleVertex, TriangleIndices){}
private:

};

*/
#endif //OPENGLSETUP_TRIANGLE_H
