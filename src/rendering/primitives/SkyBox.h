//
// Created by Sean on 7/11/2019.
//

#ifndef GAMEENGINE_SKYBOX_H
#define GAMEENGINE_SKYBOX_H

#include <memory>
#include "engine/Entity.h"
#include <rendering/buffer-objects/FrameBuffer.h>
/**
 * @class SkyBox
 * @brief Entity extension for skybox
 */
class SkyBox : public Entity
{
public:
	SkyBox(Texture texture, std::shared_ptr<Camera> camera, glm::mat4 m_projection, Shader shader);
	void render(void);
	void setShader(const Shader &shader);

private:
	Texture m_texture;
	Shader m_shader;
	std::shared_ptr<Camera> camera;
	glm::mat4 m_projection;
};


#endif //GAMEENGINE_SKYBOX_H
