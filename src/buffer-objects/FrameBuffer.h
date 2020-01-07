//
// Created by Sean on 4/16/2019.
//

#ifndef OPENGLSETUP_FRAMEBUFFER_H
#define OPENGLSETUP_FRAMEBUFFER_H
// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BufferObject.h"

/**
 * @brief Class to hold frame buffer objects and related functions
 */
class FrameBuffer : public BufferObject
{
public:
	/**
	 * @brief Default FrameBuffer constructor, runs setUp() function
	 */
    FrameBuffer();
    /**
     * @brief sets up frame buffer with ID and buffer objects
     */
    void setUp();
    /**
     * @brief Binds uniform buffer object and translates based on view
     * @param view - view to be used in rendering
     */
    void bind(glm::mat4 view);
	void unbind(void);
    glm::mat4 getProjection();
    GLuint getTextureBuffer();
private:
    GLuint m_ID;
    GLuint m_rbo;
    GLuint m_uboMatrices;
    GLuint m_textureColorbuffer;
    glm::mat4 m_projection;
};


#endif //OPENGLSETUP_FRAMEBUFFER_H
