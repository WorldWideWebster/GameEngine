//
// Created by Sean on 1/6/2020.
//

#ifndef OPENGLSETUP_BUFFEROBJECT_H
#define OPENGLSETUP_BUFFEROBJECT_H
// OpenGL includes
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BufferObject
{
public:

	/**
	 * @brief sets up frame buffer with ID and buffer objects
	 */
	virtual void setUp(){};
	/**
	 * @brief Binds uniform buffer object and translates based on view
	 * @param view - view to be used in rendering
	 */
	virtual void bind(){};
	virtual void unbind(void){};
	virtual GLuint getTextureBuffer(){ return 1; };
	virtual glm::mat4 getProjection(){ return glm::mat4(1);}
};


#endif //OPENGLSETUP_BUFFEROBJECT_H
