//
// Created by Sean on 7/11/2019.
//

#ifndef OPENGLSETUP_SKYBOX_H
#define OPENGLSETUP_SKYBOX_H

#include "../mesh.h"
#include "../RenderBuffer.h"
/**
 * @class SkyBox
 * @brief Mesh extension for skybox
 */
class SkyBox
{
public:
	SkyBox(Texture texture, Camera *camera, RenderBuffer *renderBuffer);
	void Draw(Shader shader);
private:
	Texture texture;
	Cube *cube = new Cube();
	Camera *camera;
	RenderBuffer *renderBuffer;
};


#endif //OPENGLSETUP_SKYBOX_H
