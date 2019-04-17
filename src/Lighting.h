//
// Created by Sean on 4/14/2019.
//

#ifndef OPENGLSETUP_LIGHTING_H
#define OPENGLSETUP_LIGHTING_H
#include "shader.h"
#include "camera.h"

void doLighting(Shader *shader, Camera camera, glm::vec3 lightPos, bool flashlight);


#endif //OPENGLSETUP_LIGHTING_H
