//
// Created by Sean on 11/7/2019.
//

#ifndef OPENGLSETUP_SHADERLIBRARY_H
#define OPENGLSETUP_SHADERLIBRARY_H

#include <filesystem>
#include <vector>
#include <iostream>
#include <shader/shader.h>

namespace fs = std::filesystem;
std::string path = "/path/to/directory";

class ShaderLibrary
{
public:
void addShader(Shader targetShader);
void refreshLibrary(void);

private:
static std::vector<Shader> shaders;

};


#endif //OPENGLSETUP_SHADERLIBRARY_H
