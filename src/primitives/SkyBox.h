//
// Created by Sean on 7/11/2019.
//

#ifndef OPENGLSETUP_SKYBOX_H
#define OPENGLSETUP_SKYBOX_H

#include <memory>
#include "../Entity.h"
#include "buffer-objects/FrameBuffer.h"
/**
 * @class SkyBox
 * @brief Entity extension for skybox
 */
class SkyBox
{
public:
	SkyBox(Texture texture, std::shared_ptr<Camera> camera, FrameBuffer *frameBuffer);
	void Draw(Shader shader);
private:
	Texture m_texture;
	Shader m_shader;
	std::shared_ptr<Camera> camera;
	FrameBuffer *frameBuffer;
};


#endif //OPENGLSETUP_SKYBOX_H
