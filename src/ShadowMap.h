//
// Created by Sean on 1/12/2020.
//

#ifndef OPENGLSETUP_SHADOWMAP_H
#define OPENGLSETUP_SHADOWMAP_H
// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static unsigned int *depthMapPtr = nullptr;

inline void setShadowMap(unsigned int *depthMap){depthMapPtr = depthMap;}
inline unsigned int getShadowMap(void) { return *depthMapPtr;}

#endif //OPENGLSETUP_SHADOWMAP_H
