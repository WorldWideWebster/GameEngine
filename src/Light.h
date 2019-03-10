//
// Created by Sean on 3/6/2019.
//

#ifndef OPENGLSETUP_LIGHT_H
#define OPENGLSETUP_LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum LightType
{
    AMBIENT_LIGHT,
    DIRECTIONAL_LIGHT,
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
    short type;         // Type of light

    // TODO: this stuff can probably be converted to a union to make things faster
    glm::vec3 position;      // Position of light
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    Light();
    Light(glm::vec3 pos);
    Light(short type);
public:

    void setType(short type);

    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setcutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);

    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);

    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);


    glm::vec3 getPosition(void);
    glm::vec3 getDirection(void);
    float getcutOff(void);
    float getOuterCutOff(void);

    glm::vec3 getAmbient(void);
    glm::vec3 getDiffuse(void);
    glm::vec3 getSpecular(void);

    float getConstant(void);
    float getLinear(void);
    float getQuadratic(void);
    short getType(void);
};




#endif //OPENGLSETUP_LIGHT_H
