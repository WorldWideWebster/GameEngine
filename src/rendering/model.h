//
// Created by Sean on 10/19/2018.
//

#ifndef GAMEENGINE_MODEL_H
#define GAMEENGINE_MODEL_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <rendering/shader/shader.h>
#include <rendering/mesh.h>

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
    Model(){};
    Model(char *path);
    Model(Mesh *targetMesh);
    Model(std::vector<Mesh> meshVector);
    void Draw(Shader shader);
    void Draw(Shader shader, unsigned int depthMap);
private:

    /* Functions */
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

Material loadMaterial(aiMaterial *mat);


#endif //GAMEENGINE_MODEL_H
