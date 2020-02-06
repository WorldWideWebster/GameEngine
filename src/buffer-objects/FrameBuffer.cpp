//
// Created by Sean on 4/16/2019.
//

// STD Library Includes
#include <iostream>

// OpenGL includes
#include "main_defs.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
    this->setUp();
}

void FrameBuffer::setUp()
{
	// TODO: Move this?
	this->m_projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, RENDER_DISTANCE_NEAR, RENDER_DISTANCE_FAR);

    // framebuffer configuration
    // -------------------------
    glGenFramebuffers(1, &this->m_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
    // create a color attachment texture
    glGenTextures(1, &this->m_textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, this->m_textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &this->m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, this->m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->m_rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glGenBuffers(1, &this->m_uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, this->m_uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, this->m_uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    // TODO: Move this to somewhere easily accessible
    glBindBuffer(GL_UNIFORM_BUFFER, this->m_uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(this->m_projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void FrameBuffer::bind(glm::mat4 view)
{
    glBindBuffer(GL_UNIFORM_BUFFER, this->m_uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // render
    // ------
    // bind to framebuffer and draw scene as we normally would to color texture
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::unbind(void)
{
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f,
				 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
}

glm::mat4 FrameBuffer::getProjection()
{
    return this->m_projection;
}

GLuint FrameBuffer::getTextureBuffer()
{
    return this->m_textureColorbuffer;
}

GLuint* FrameBuffer::getTextureBufferPtr()
{
    return &this->m_textureColorbuffer;
}
