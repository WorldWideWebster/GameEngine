//
// Created by Sean on 10/19/2018.
//

#ifndef OPENGLSETUP_MODEL_H
#define OPENGLSETUP_MODEL_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

/* Material struct to convert assimp to usable material
 * also allows for loading of models without a texture
 *
 */
struct Material
{
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
    float shininess;
};

class Model
{
public:
    /* Model Data */
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
    /* Functions */
    Model(char *path);
    void Draw(Shader shader);
private:

    /* Functions */
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

Material loadMaterial(aiMaterial *mat);


#endif //OPENGLSETUP_MODEL_H