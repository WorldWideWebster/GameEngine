//
// Created by Sean on 3/6/2019.
//

#ifndef GAMEENGINE_LIGHT_H
#define GAMEENGINE_LIGHT_H

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <rendering/shader/shader.h>
#include "engine/Entity.h"


const glm::vec3 DEFAULT_COLOR (0.5f, 0.5f, 0.5f);

/* @brief: Light Class - ambient light object
 *
 *
 * @Purpose: Place to store lights
 *
 */
class Light
{
public:
	Light();
	Light(std::string ID);
	Light(glm::vec3 color, std::string ID);

	std::string m_ID;
	glm::vec3 m_attached_entity_offset_position;
	glm::vec3 m_attached_entity_offset_rotation;

    void setColor(glm::vec3 color);

	void setID(std::string ID);
	virtual void render(Shader *targetShader);
	void toggle(bool toggle);
	inline virtual void updatePosition(glm::vec3 position){}
	inline virtual void updateDirection(glm::vec3 direction){}
	virtual void attachToEntity(std::shared_ptr<Entity> targetEntity, glm::vec3 offset = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));
	inline virtual std::shared_ptr<Entity> getAttachedEntity(void){return m_targetEntity;};

	void setShaderColor(Shader *targetShader);

	/**
	 * @brief Sets shader shadow cast to light object's status
	 * @param targetShader - Shader to send light shadow to
	 */
	void setShaderShadowCast(Shader *targetShader);

    glm::vec3 getColor(void);

	virtual glm::vec3 getPosition(void);
	virtual glm::vec3 getDirection(void);

	/**
	 * @brief Toggles shadow casting of light
	 * @param status - boolean to determine if light is being turned on/off
	 */
	void toggleShadowCast(bool status);
private:
	glm::vec3 m_color;
	std::shared_ptr<Entity> m_targetEntity = nullptr;

	bool m_casts_shadow = false; 	/// Whether light casts shadow
	bool m_on;				/// Is light on?
};




#endif //GAMEENGINE_LIGHT_H
