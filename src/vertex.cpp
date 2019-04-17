//
// Created by Sean on 11/16/2018.
//

#include "vertex.h"

std::vector<Vertex> fillVertexVector(std::vector<float> verticesIn, std::vector<float> normsIn, std::vector<float> texcIn)
{
    std::vector<Vertex> outVert = {};
    Vertex curVert;
    for(int i = 0; i < verticesIn.size(); i+=3)
    {
        curVert.Position = glm::vec3(verticesIn[i], verticesIn[i+1], verticesIn[i+2]);
        curVert.Normal = glm::vec3(normsIn[i], normsIn[i+1], normsIn[i+2]);
        outVert.push_back(curVert);
    }
    for(int i = 0; i < verticesIn.size(); i+=2)
    {
        outVert[i/2].TexCoords = glm::vec2(texcIn[i], texcIn[i+1]);
    }
    for(int i = 0; i < outVert.size();i+=3)
    {
        // Shortcuts for vertices
        glm::vec3 & v0 = outVert[i+0].Position;
        glm::vec3 & v1 = outVert[i+1].Position;
        glm::vec3 & v2 = outVert[i+2].Position;

        // Shortcuts for UVs
        glm::vec2 & uv0 = outVert[i+0].TexCoords;
        glm::vec2 & uv1 = outVert[i+1].TexCoords;
        glm::vec2 & uv2 = outVert[i+2].TexCoords;

        // Edges of the triangle : position delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        outVert[i+0].Tangent = tangent;
        outVert[i+1].Tangent = tangent;
        outVert[i+2].Tangent = tangent;

        outVert[i+0].Bitangent = bitangent;
        outVert[i+1].Bitangent = bitangent;
        outVert[i+2].Bitangent = bitangent;
    }
    return outVert;
}

void VertTanCalc(Vertex *verticesIn, GLuint nrOfVertices)
{
    for(int i = 0; i < nrOfVertices; i+=3)
    {
        // Shortcuts for vertices
        glm::vec3 & v0 = verticesIn[i+0].Position;
        glm::vec3 & v1 = verticesIn[i+1].Position;
        glm::vec3 & v2 = verticesIn[i+2].Position;

        // Shortcuts for UVs
        glm::vec2 & uv0 = verticesIn[i+0].TexCoords;
        glm::vec2 & uv1 = verticesIn[i+1].TexCoords;
        glm::vec2 & uv2 = verticesIn[i+2].TexCoords;

        // Edges of the triangle : position delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        verticesIn[i+0].Tangent = tangent;
        verticesIn[i+1].Tangent = tangent;
        verticesIn[i+2].Tangent = tangent;

        verticesIn[i+0].Bitangent = bitangent;
        verticesIn[i+1].Bitangent = bitangent;
        verticesIn[i+2].Bitangent = bitangent;
    }
}


std::vector<Vertex> vertexFromVertices(std::vector<float> vertexIn)
{
    std::vector<Vertex> outVert = {};
    Vertex curVert;
    float x, y ,z , a, b;
    for(int i = 0; i < vertexIn.size();)
    {
        x = vertexIn[i++];
        y = vertexIn[i++];
        z = vertexIn[i++];
        curVert.Position = glm::vec3(x, y, z);

        x = vertexIn[i++];
        y = vertexIn[i++];
        z = vertexIn[i++];
        curVert.Normal = glm::vec3(x, y, z);

        a = vertexIn[i++];
        b = vertexIn[i++];
        curVert.TexCoords = glm::vec2(a, b);

        outVert.push_back(curVert);
    }

    for(int i = 0; i < outVert.size();i+=3)
    {
        // Shortcuts for vertices
        glm::vec3 & v0 = outVert[i+0].Position;
        glm::vec3 & v1 = outVert[i+1].Position;
        glm::vec3 & v2 = outVert[i+2].Position;

        // Shortcuts for UVs
        glm::vec2 & uv0 = outVert[i+0].TexCoords;
        glm::vec2 & uv1 = outVert[i+1].TexCoords;
        glm::vec2 & uv2 = outVert[i+2].TexCoords;

        // Edges of the triangle : position delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        outVert[i+0].Tangent = tangent;
        outVert[i+1].Tangent = tangent;
        outVert[i+2].Tangent = tangent;

        outVert[i+0].Bitangent = bitangent;
        outVert[i+1].Bitangent = bitangent;
        outVert[i+2].Bitangent = bitangent;
    }
    return outVert;
}

void VertNormCalc(Vertex *verticesIn, GLuint nrOfVertices)
{
    for(int i = 0; i < nrOfVertices; i++)
    {
        if (i == 0)
        {

        }
        else if (i == (nrOfVertices - 1))
        {

        }
        else
        {
        }
    }
}
