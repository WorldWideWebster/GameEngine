//
// Created by Sean on 4/16/2019.
//

#ifndef gBuffer_H
#define gBuffer_H
// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BufferObject.h"

/**
 * @brief Class to hold frame buffer objects and related functions
 */
class gBuffer : public BufferObject
{
public:
	/**
	 * @brief Default gBuffer constructor, runs setUp() function
	 */
    gBuffer();
    /**
     * @brief sets up frame buffer with ID and buffer objects
     */
    void setUp();
    /**
     * @brief Binds uniform buffer object and translates based on view
     * @param view - view to be used in rendering
     */
    void bind(void);
	void unbind(void);
	void writeToExternalBuffer(GLuint buffer, GLuint bufferTex);
	void bindTextures(void);

	GLuint getPosition(void) {return this->m_position;}
	GLuint getNormal(void) {return this->m_normal;}
	GLuint getAlbedoSpec(void) {return this->m_albedoSpec;}
private:
    GLuint m_ID;
    GLuint m_rbo;
    GLuint m_position;
    GLuint m_normal;
    GLuint m_albedoSpec;
};


#endif //gBuffer_H
