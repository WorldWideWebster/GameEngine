//
// Created by Sean on 3/6/2019.
//

#ifndef OPENGLSETUP_LIGHT_H
#define OPENGLSETUP_LIGHT_H

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader/shader.h"
#include "../Entity.h"


/* @brief: Light Class - ambient light object
 *
 *
 * @Purpose: Place to store lights
 *
 */
class Light
{
private:
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    std::shared_ptr<Entity> m_targetEntity = nullptr;

    bool m_on;
public:
	Light(std::string ID);
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, std::string ID);

	std::string m_ID;
	glm::vec3 m_attached_entity_offset_position;
	glm::vec3 m_attached_entity_offset_rotation;

    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);

	virtual void render(Shader *targetShader);
	void toggle(bool toggle);
	inline virtual void updatePosition(glm::vec3 position){}
	inline virtual void updateDirection(glm::vec3 direction){}
	virtual void attachToEntity(std::shared_ptr<Entity> targetEntity, glm::vec3 offset = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));
	inline virtual std::shared_ptr<Entity> getAttachedEntity(void){return m_targetEntity;};

	void setShaderAmbient(Shader *targetShader);
	void setShaderDiffuse(Shader *targetShader);
	void setShaderSpecular(Shader *targetShader);

    glm::vec3 getAmbient(void);
    glm::vec3 getDiffuse(void);
    glm::vec3 getSpecular(void);
	virtual glm::vec3 getPosition(void);
	virtual glm::vec3 getDirection(void);

};




#endif //OPENGLSETUP_LIGHT_H
