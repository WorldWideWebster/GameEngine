//
// Created by Sean on 3/6/2019.
//

#ifndef OPENGLSETUP_LIGHT_H
#define OPENGLSETUP_LIGHT_H


#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"


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
    bool m_on;
public:
	Light(std::string ID);
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, std::string ID);

	std::string m_ID;

    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);

	virtual void render(Shader *targetShader);
	virtual void turnOff();
	virtual void turnOn();


	void setShaderAmbient(Shader *targetShader);
	void setShaderDiffuse(Shader *targetShader);
	void setShaderSpecular(Shader *targetShader);

    glm::vec3 getAmbient(void);
    glm::vec3 getDiffuse(void);
    glm::vec3 getSpecular(void);
};




#endif //OPENGLSETUP_LIGHT_H
