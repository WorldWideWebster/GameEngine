//
// Created by Sean on 7/11/2019.
//
#include <memory>
#include "SkyBox.h"
#include "Primitive.h"
#include "../RenderBuffer.h"

SkyBox::SkyBox(Texture texture, Camera *camera, RenderBuffer *renderBuffer)
{
	//this->camera = camera;
	//this->renderBuffer = renderBuffer;
}


void SkyBox::Draw(Shader shader)
{
	/*
	// Check if there are any textures
	if(textures.size())
	{
		// bind appropriate textures
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		GLuint normalNr = 1;
		GLuint heightNr = 1;

		for (GLuint i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); //activate proper texture unit before binding
			// retreive texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer GLuint to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer GLuint to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer GLuint to stream

			// Set the sampler
			shader.setFloat(("material." + name + number).c_str(), i);
			// Bind the texture
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);
	}
	else
	{
		// If there are no textures, use default texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->getDefaultTexture());
		glActiveTexture(GL_TEXTURE0);

	}


	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shader.use();
	glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
	shader.setMat4("view", view);
	shader.setMat4("projection", renderBuffer->getProjection());

	// Draw Mesh
	glBindVertexArray(this->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default

	 */
}