//
// Created by Sean on 3/6/2019.
//

#ifndef OPENGLSETUP_LIGHT_H
#define OPENGLSETUP_LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"
enum LightType
{
    POINT_LIGHT,
    SPOT_LIGHT,
};


/* Light Class
 *
 * @Purpose: Place to store lights
 *
 *  TODO: More comments on light class
 */
class Light
{
private:
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
public:
	Light();
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);

    glm::vec3 getAmbient(void);
    glm::vec3 getDiffuse(void);
    glm::vec3 getSpecular(void);
};




#endif //OPENGLSETUP_LIGHT_H
