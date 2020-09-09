//
// Created by Sean on 4/16/2019.
//

// STD Library Includes
#include <iostream>

// OpenGL includes
#include "main_defs.h"
#include "gBuffer.h"

gBuffer::gBuffer()
{
    this->setUp();
}

void gBuffer::setUp()
{
    // framebuffer configuration
    // -------------------------
    glGenFramebuffers(1, &this->m_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);


	// configure g-buffer framebuffer
	// ------------------------------
	glGenFramebuffers(1,  &this->m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
    // create a color attachment texture
	// position color buffer
	glGenTextures(1, &this->m_position);
	glBindTexture(GL_TEXTURE_2D, this->m_position);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_position, 0);

	// normal color buffer
	glGenTextures(1, &this->m_normal);
	glBindTexture(GL_TEXTURE_2D, this->m_normal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->m_normal, 0);

	// color buffer
	glGenTextures(1, &this->m_albedo);
	glBindTexture(GL_TEXTURE_2D, this->m_albedo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->m_albedo, 0);

	// specular color buffer
	glGenTextures(1, &this->m_spec);
	glBindTexture(GL_TEXTURE_2D, this->m_spec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, this->m_spec, 0);

	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
	unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);

	// create and attach depth buffer (renderbuffer)
	glGenRenderbuffers(1, &this->m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, this->m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->m_rbo);
	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gBuffer::bindForWriting(void)
{
    // render
    // ------
    // bind to framebuffer and draw scene as we normally would to color texture
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void gBuffer::bindForReading(void)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_ID);
}

void gBuffer::unbind(void)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void gBuffer::writeToExternalBuffer(GLuint buffer, GLuint bufferTex)
{
//	// 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
//	// ----------------------------------------------------------------------------------
//	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_ID);
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer); // write to default framebuffer
//	// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
//	// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the
//	// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
//	glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	// Bind input FBO + texture to a color attachment
//	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_ID);
//	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D,  this->m_albedoSpec, 0);
//	glReadBuffer(GL_COLOR_ATTACHMENT6);
//
//	// Bind destination FBO + texture to another color attachment
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer);
//	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, bufferTex, 0);
//	glDrawBuffer(GL_COLOR_ATTACHMENT7);
//
//	// specify source, destination drawing (sub)rectangles.
//	glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT,
//					  0, 0, SCR_WIDTH, SCR_HEIGHT,
//					  GL_COLOR_BUFFER_BIT, GL_NEAREST);
//
//	// unbind the color attachments
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, 0, 0);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, 0, 0);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void gBuffer::bindTextures(void)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_position);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->m_normal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->m_albedo);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->m_spec);
}


