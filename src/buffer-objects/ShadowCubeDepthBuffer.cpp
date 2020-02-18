//
// Created by Sean on 4/16/2019.
//

// STD Library Includes
#include <iostream>

// OpenGL includes
#include "main_defs.h"
#include "ShadowCubeDepthBuffer.h"

ShadowCubeDepthBuffer::ShadowCubeDepthBuffer()
{
    this->setUp();
}

void ShadowCubeDepthBuffer::setUp()
{
	// Configure DepthMap FBO
	glGenFramebuffers(1, &this->m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);

	// create depth texture;
	glGenTextures(1, &this->m_depthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_depthCubeMap);
	for(unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
					 GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// Attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->m_depthCubeMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowCubeDepthBuffer::bind(glm::mat4 view)
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
}

void ShadowCubeDepthBuffer::unbind(void)
{
	// Unbind the buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void ShadowCubeDepthBuffer::doDebugDepth(void)
{

}

GLuint *ShadowCubeDepthBuffer::getShadowMap()
{
    return &this->m_depthCubeMap;
}

GLuint ShadowCubeDepthBuffer::getTextureBuffer()
{
	return this->m_depthCubeMap;
}





