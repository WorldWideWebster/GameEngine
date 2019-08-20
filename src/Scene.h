//
// Created by Sean on 8/8/2019.
//

#ifndef OPENGLSETUP_SCENE_H
#define OPENGLSETUP_SCENE_H
#include <vector>
#include "Entity.h"

class Scene
{
public:
	Scene();
	void addEntity(Entity targetEntity);
	void render(Shader *shader);
private:
	std::vector<Entity> entities;
};


#endif //OPENGLSETUP_SCENE_H
