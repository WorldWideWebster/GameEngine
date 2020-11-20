//
// Created by Sean on 4/16/2019.
//

#ifndef SHADOWCUBEDEPTHBUFFER_H
#define SHADOWCUBEDEPTHBUFFER_H
// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <rendering/shader/shader.h>
#include <rendering/buffer-objects/BufferObject.h>


/**
 * @brief Class to hold shadow depth buffer objects and related functions
 *
 *
 * Shadow depth buffer state machine works like so
 *
 * setup -> renderloop[prime shadow buffer -> render scene from light POV - > uinbind shadow buffer -> render scene normally]
 */
class ShadowCubeDepthBuffer : public BufferObject
{
public:
	/**
	 * @brief Default FrameBuffer ShadowCubeDepthBuffer, runs setUp() function
	 */
	ShadowCubeDepthBuffer();

	/**
	 * @brief sets up frame buffer with ID and buffer objects
	 */
	void setUp();

	/**
     * @brief Binds shadow buffer setting it up to capture depths
	 * @param lightPos position of directional light
	 * @param simpleDepthShader depth shader to be used
	 */
	void bind();

	/**
	 * @brief Unbinds the shadow depth buffer so we don't keep writing to it
	 */
	void unbind(void);

	/**
	 * @brief Binds the shadow depth buffer texture ID to a GL_TEXTURE
	 */
	void bindDepthMapTexture(void);

	void doDebugDepth(void);

	GLuint *getShadowMap();
	GLuint getTextureBuffer();

private:
	GLuint m_ID;
	unsigned int m_depthCubeMap;
};


#endif //SHADOWCUBEDEPTHBUFFER_H

