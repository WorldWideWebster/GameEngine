//
// Created by Sean on 8/8/2019.
//

#ifndef OPENGLSETUP_SCENE_H
#define OPENGLSETUP_SCENE_H
#include <vector>
#include <memory>

#include <glm/ext.hpp>


#include "camera.h"
#include "Entity.h"
#include "lighting/PointLight.h"
#include "lighting/DirectionalLight.h"
#include "lighting/SpotLight.h"
#include "buffer-objects/FrameBuffer.h"

class Scene
{
public:
	Scene();
	void addEntity(std::shared_ptr<Entity> targetEntity);
	void addLight(std::shared_ptr<Light> targetLight);
	void addCamera(void);
	void render(Shader *shader, FrameBuffer *frameBuffer);
	void setActiveScene(void);
	void setInactiveScene(void);
	void setNumberOfPointLights(int numLights);
	void setNumberOfDirLights(int numLights);
	void setNumberOfSpotLights(int numLights);
	void setShaderPointLights(Shader *shader);
	void setShaderDirLights(Shader *shader);
	void setShaderSpotLights(Shader *shader);
	void setDefaultCamera(int cameraNum);
	std::shared_ptr<Camera> getDefaultCamera(void);

	std::shared_ptr<Entity> getEntityByID(std::string ID);
	std::shared_ptr<Light> getLightByID(std::string ID);

	void setLightPosition(std::string targetID, glm::vec3 targetPosition);
	void setLightDirection(std::string targetID, glm::vec3 targetDirection);
	void toggleLight(std::string targetID, bool toggle);

	void setEntityPosition(std::string targetID, glm::vec3 targetPosition);
	void setEntityRotationDeg(std::string targetID, float targetRotAngle, glm::vec3 targetRotation);
	void setEntityScale(std::string targetID, glm::vec3 targetScale);

	std::vector<std::string> showSceneDetails(void);
private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::shared_ptr<Light>> m_lights;
	std::vector<Camera> m_cameras;
	std::shared_ptr<Camera> m_default_camera;
	bool m_active;
	int m_num_point_lights;
	int m_num_dir_lights;
	int m_num_spot_lights;
	// std::unique_ptr<Camera> m_default_camera;
};


#endif //OPENGLSETUP_SCENE_H
