//
// Created by Sean on 4/16/2019.
//

#ifndef OPENGLSETUP_RENDERBUFFER_H
#define OPENGLSETUP_RENDERBUFFER_H
// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RenderBuffer
{
public:
    RenderBuffer();
    void setUp();
    void bindAndBuffer(glm::mat4 view);
	void bindDefault(void);
    glm::mat4 getProjection();
    GLuint getTextureColorbuffer();
private:
    GLuint ID;
    GLuint rbo;
    GLuint uboMatrices;
    GLuint textureColorbuffer;
    glm::mat4 projection;
};


#endif //OPENGLSETUP_RENDERBUFFER_H
