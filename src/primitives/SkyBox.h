//
// Created by Sean on 7/11/2019.
//

#ifndef OPENGLSETUP_SKYBOX_H
#define OPENGLSETUP_SKYBOX_H

#include <memory>
#include "../Entity.h"
#include "../RenderBuffer.h"
/**
 * @class SkyBox
 * @brief Entity extension for skybox
 */
class SkyBox
{
public:
	SkyBox(Texture texture, std::shared_ptr<Camera> camera, RenderBuffer *renderBuffer);
	void Draw(Shader shader);
private:
	Texture m_texture;
	std::shared_ptr<Camera> camera;
	RenderBuffer *renderBuffer;
};


#endif //OPENGLSETUP_SKYBOX_H
