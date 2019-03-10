//
// Created by Sean on 12/9/2018.
//

#include "renderutil.h"

void RenderUtil::clearScreen()
{
    //TODO: stencil buffer

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::initGraphics()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    //TODO: depth clamp

    glEnable(GL_FRAMEBUFFER_SRGB);

}
