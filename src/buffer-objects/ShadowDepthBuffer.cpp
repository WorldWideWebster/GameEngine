//
// Created by Sean on 4/16/2019.
//

// STD Library Includes
#include <iostream>

// OpenGL includes
#include "main_defs.h"
#include "ShadowDepthBuffer.h"

ShadowDepthBuffer::ShadowDepthBuffer()
{
    this->setUp();
}

void ShadowDepthBuffer::setUp()
{
	// Configure DepthMap FBO
	glGenFramebuffers(1, &this->m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);

	// create depth texture;
	glGenTextures(1, &this->m_depthMap);
	glBindTexture(GL_TEXTURE_2D, this->m_depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// Attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->m_depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowDepthBuffer::bind(glm::mat4 view)
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
}

void ShadowDepthBuffer::unbind(void)
{
	// Unbind the buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// reset viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}

void ShadowDepthBuffer::doDebugDepth(void)
{

}

GLuint *ShadowDepthBuffer::getShadowMap()
{
    return &this->m_depthMap;
}

GLuint ShadowDepthBuffer::getTextureBuffer()
{
	return this->m_depthMap;
}





