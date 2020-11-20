//
// Created by Sean on 4/14/2019.
//

#ifndef GAMEENGINE_LIGHTING_H
#define GAMEENGINE_LIGHTING_H
#include <rendering/shader/shader.h>
#include "camera.h"

void doLighting(Shader *shader, Camera camera, glm::vec3 lightPos, bool flashlight);


#endif //GAMEENGINE_LIGHTING_H
