//
// Created by Sean on 8/30/2018.
//

#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;


    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // similiar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    unsigned int geometry;
    if(geometryPath != nullptr)
    {
        const char *gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if(geometryPath != nullptr)
    {
        glAttachShader(ID, geometry);
    }
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath != nullptr)
    {
        glDeleteShader(geometry);
    }
}

void Shader::use()
{
    glUseProgram(ID);
}
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog <<
                    "\n -- ----------------------------------------- --" << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog <<
                      "\n -- ----------------------------------------- --" << std::endl;        }
    }
}

void Shader::addLight(Light light)
{
    this->lights.push_back(light);
    switch(light.getType())
    {
        case AMBIENT_LIGHT:
            break;
        case DIRECTIONAL_LIGHT:
            num_dir_lights++;
            break;
        case POINT_LIGHT:
            num_point_lights++;
            break;
        case SPOT_LIGHT:
            num_spot_lights++;
            break;
        default:
            break;
    }
}
/*
void Shader::doLighting(void)
{
    this->use();
    this->setVec3("viewPos", this->camera->Position);

    this->setInt("num_point_lights", num_point_lights);
    this->setInt("num_dir_lights", num_dir_lights);
    this->setInt("num_spot_lights", num_spot_lights);
    this->setFloat("material.shininess", 32.0f);

    for(int i = 0, di = 0, pi = 0, si = 0; i++; i < this->lights.size())
    {
        switch(this->lights[i].getType())
        {
            case AMBIENT_LIGHT:
                break;
            case DIRECTIONAL_LIGHT:
                this->setVec3("dirLights[di].direction", this->lights[i].getDirection());
                this->setVec3("dirLights[di].ambient", this->lights[i].getAmbient());
                this->setVec3("dirLights[di].diffuse", this->lights[i].getDiffuse());
                this->setVec3("dirLights[di].specular", this->lights[i].getSpecular());
                di++;
                break;
            case POINT_LIGHT:
                this->setVec3("pointLights[pi].position", this->lights[i].getPosition());
                this->setVec3("pointLights[pi].ambient", this->lights[i].getAmbient());
                this->setVec3("pointLights[pi].diffuse", this->lights[i].getDiffuse());
                this->setVec3("pointLights[pi].specular", this->lights[i].getSpecular());
                this->setFloat("pointLights[pi].constant", this->lights[i].getConstant());
                this->setFloat("pointLights[pi].linear", this->lights[i].getLinear());
                this->setFloat("pointLights[pi].quadratic", this->lights[i].getQuadratic());
                pi++;
                break;
            case SPOT_LIGHT:
                this->setVec3("spotLights[si].position", this->lights[i].getPosition());
                this->setVec3("spotLights[si].direction", this->lights[i].getDirection());
                this->setVec3("spotLights[si].ambient", this->lights[i].getAmbient());
                this->setVec3("spotLights[si].diffuse", this->lights[i].getDiffuse());
                this->setVec3("spotLights[0].specular", this->lights[i].getSpecular());
                this->setFloat("spotLights[0].constant", this->lights[i].getConstant());
                this->setFloat("spotLights[0].linear", this->lights[i].getLinear());
                this->setFloat("spotLights[0].quadratic", this->lights[i].getQuadratic());
                this->setFloat("spotLights[0].cutOff", this->lights[i].getcutOff());
                this->setFloat("spotLights[0].outerCutOff", this->lights[i].getOuterCutOff());
                si++;
                break;
            default:
                break;
        }


        // spotLight

    }
}

*/