//
// Created by Sean on 5/21/2019.
//

// used http://www.songho.ca/opengl/gl_sphere.html as a basis


#ifndef GAMEENGINE_ICOSPHERE_H
#define GAMEENGINE_ICOSPHERE_H

#include "Primitive.h"

class Icosahedron : public Primitive
{
public:
    Icosahedron();


private:


    std::vector<Vertex> calcVertices();
    std::vector<GLuint> calcIndices();

    // memeber vars
    float radius;                           // circumscribed radius
    float edgeLength;
    std::vector<unsigned int> lineIndices;

    // interleaved
    std::vector<float> interleavedVertices;
    int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)
};


#endif //GAMEENGINE_ICOSPHERE_H
