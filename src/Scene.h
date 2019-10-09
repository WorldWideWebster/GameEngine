//
// Created by Sean on 8/8/2019.
//

#ifndef OPENGLSETUP_SCENE_H
#define OPENGLSETUP_SCENE_H
#include <vector>
#include "Entity.h"
#include "lighting/PointLight.h"
#include "lighting/DirectionalLight.h"
#include "lighting/SpotLight.h"

class Scene
{
public:
	Scene();
	void addEntity(Entity* targetEntity);
	void addPointLight(PointLight* targetLight);
	void addDirectionalLight(DirectionalLight* targetLight);
	void addSpotLight(SpotLight* targetLight);
	void render(Shader *shader);
	void setActiveScene(void);
	void setInactiveScene(void);
	void setNumberOfPointLights(int numLights);
	void setNumberOfDirLights(int numLights);
	void setNumberOfSpotLights(int numLights);
	void setShaderPointLights(Shader *shader);
	void setShaderDirLights(Shader *shader);
	void setShaderSpotLights(Shader *shader);

private:
	std::vector<Entity> m_entities;
	std::vector<DirectionalLight> m_d_lights;
	std::vector<PointLight> m_p_lights;
	std::vector<SpotLight> m_s_lights;
	bool m_active;
	int m_num_point_lights;
	int m_num_dir_lights;
	int m_num_spot_lights;
};


#endif //OPENGLSETUP_SCENE_H
