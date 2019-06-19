//
// Created by Sean on 5/21/2019.
//

#include "Icosahedron.h"

// Default Constructor
Icosahedron::Icosahedron() : Primitive()
{
    sectorCount = 10; // latitudinal sectors
    stackCount = 10;  // vertical stacks
    radius = 1.0f;

    std::vector<Vertex> vertices = calcVertices();
    unsigned nrOfVertices = vertices.size();
    VertTanCalc(vertices.data(), nrOfVertices);

    // generate CCW index list of sphere triangles
    std::vector<GLuint> indices = calcIndices();
    unsigned nrOfIndices = indices.size();

    this->set(vertices.data(), nrOfVertices, indices.data(), nrOfIndices);
}

Icosahedron::Icosahedron(int secCount, int staCount, float rad) : Primitive()
{
    sectorCount = secCount; // latitudinal sectors
    stackCount = staCount;  // vertical stacks
    radius = rad;

    std::vector<Vertex> vertices = calcVertices();
    unsigned nrOfVertices = vertices.size();
    VertTanCalc(vertices.data(), nrOfVertices);

    // generate CCW index list of sphere triangles
    std::vector<GLuint> indices = calcIndices();
    unsigned nrOfIndices = indices.size();

    this->set(vertices.data(), nrOfVertices, indices.data(), nrOfIndices);
}


///////////////////////////////////////////////////////////////////////////////
// compute 12 vertices of icosahedron using spherical coordinates
// The north pole is at (0, 0, r) and the south pole is at (0,0,-r).
// 5 vertices are placed by rotating 72 deg at elevation 26.57 deg (=atan(1/2))
// 5 vertices are placed by rotating 72 deg at elevation -26.57 deg
///////////////////////////////////////////////////////////////////////////////
std::vector<Vertex> Icosahedron::calcVertices()
{
    // constants
    const float PI = 3.1415926f;
    const float H_ANGLE = PI / 180 * 72;    // 72 degree = 360 / 5
    const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree

    std::vector<Vertex> vertices(12);    // array of 12 vertices (x,y,z)
    int i1, i2;                             // indices
    float z, xy;                            // coords
    float hAngle1 = -PI / 2 - H_ANGLE / 2;  // start from -126 deg at 1st row
    float hAngle2 = -PI / 2;                // start from -90 deg at 2nd row

    // the first top vertex at (0, 0, r)
    vertices[0].position = glm::vec3(0, 0, radius);


    // compute 10 vertices at 1st and 2nd rows
    for(int i = 1; i <= 5; ++i)
    {
        i1 = i;         // index for 1st row
        i2 = (i + 5);   // index for 2nd row

        z  = radius * sinf(V_ANGLE);            // elevaton
        xy = radius * cosf(V_ANGLE);            // length on XY plane

        Vertex vert1;
        vertex vert2;

        vert1.Position.x = xy * cosf(hAngle1);      // x
        vert2.Position.x = xy * cosf(hAngle2);
        vert1.Position.y = xy * sinf(hAngle1);  // y
        vert2.Position.y = xy * sinf(hAngle2);
        vert1.Position.z = z;                   // z
        vert2.Position.z = -z;

        vertices[i1] = vert1;
        vertices[i2] = vert2;
        // next horizontal angles
        hAngle1 += H_ANGLE;
        hAngle2 += H_ANGLE;
    }

    // the last bottom vertex at (0, 0, -r)
    i1 = 11;
    vertices[i1].Position = glm::vec3(0, 0, -radius);
    return vertices;
}


///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
// each triangle is independent (no shared vertices)
// NOTE: The texture coords are offset in order to align coords to image pixels
//    (S,0)  3S  5S  7S  (9S,0)
//       /\  /\  /\  /\  /\             //
//      /__\/__\/__\/__\/__\(10S,T)     //
// (0,T)\  /\  /\  /\  /\  /\           //
//       \/__\/__\/__\/__\/__\(11S,2T)  //
//  (S,2T)\  /\  /\  /\  /\  /          //
//         \/  \/  \/  \/  \/           //
//    (2S,3T)  4S  6S  8S  (10S,3T)
// where S = 186/2048 = 0.0908203
//       T = 322/1024 = 0.3144531, If texture size is 2048x1024, S=186, T=322
///////////////////////////////////////////////////////////////////////////////
void Icosahedron::buildVertices()
{
    //const float S_STEP = 1 / 11.0f;         // horizontal texture step
    //const float T_STEP = 1 / 3.0f;          // vertical texture step
    const float S_STEP = 186 / 2048.0f;     // horizontal texture step
    const float T_STEP = 322 / 1024.0f;     // vertical texture step

    // compute 12 vertices of icosahedron
    std::vector<Vertex> tmpVertices = computeVertices();

    // clear memory of prev arrays
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);

    float *v0, *v1, *v2, *v3, *v4, *v11;                // vertex positions
    float n[3];                                         // face normal
    float t0[2], t1[2], t2[2], t3[2], t4[2], t11[2];    // texCoords
    unsigned int index = 0;

    // compute and add 20 tiangles
    v0 = &tmpVertices[0];       // 1st vertex
    v11 = &tmpVertices[11 * 3]; // 12th vertex
    for(int i = 1; i <= 5; ++i)
    {
        // 4 vertices in the 2nd row
        v1 = &tmpVertices[i * 3];
        if(i < 5)
            v2 = &tmpVertices[(i + 1) * 3];
        else
            v2 = &tmpVertices[3];

        v3 = &tmpVertices[(i + 5) * 3];
        if((i + 5) < 10)
            v4 = &tmpVertices[(i + 6) * 3];
        else
            v4 = &tmpVertices[6 * 3];

        // texture coords
        t0[0] = (2 * i - 1) * S_STEP;   t0[1] = 0;
        t1[0] = (2 * i - 2) * S_STEP;   t1[1] = T_STEP;
        t2[0] = (2 * i - 0) * S_STEP;   t2[1] = T_STEP;
        t3[0] = (2 * i - 1) * S_STEP;   t3[1] = T_STEP * 2;
        t4[0] = (2 * i + 1) * S_STEP;   t4[1] = T_STEP * 2;
        t11[0]= 2 * i * S_STEP;         t11[1]= T_STEP * 3;

        // add a triangle in 1st row
        Icosahedron::computeFaceNormal(v0, v1, v2, n);
        addVertices(v0, v1, v2);
        addNormals(n, n, n);
        addTexCoords(t0, t1, t2);
        addIndices(index, index+1, index+2);

        // add 2 triangles in 2nd row
        Icosahedron::computeFaceNormal(v1, v3, v2, n);
        addVertices(v1, v3, v2);
        addNormals(n, n, n);
        addTexCoords(t1, t3, t2);
        addIndices(index+3, index+4, index+5);

        Icosahedron::computeFaceNormal(v2, v3, v4, n);
        addVertices(v2, v3, v4);
        addNormals(n, n, n);
        addTexCoords(t2, t3, t4);
        addIndices(index+6, index+7, index+8);

        // add a triangle in 3rd row
        Icosahedron::computeFaceNormal(v3, v11, v4, n);
        addVertices(v3, v11, v4);
        addNormals(n, n, n);
        addTexCoords(t3, t11, t4);
        addIndices(index+9, index+10, index+11);

        // add 6 edge lines per iteration
        addLineIndices(index);

        // next index
        index += 12;
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}