//
// Created by Sean on 10/18/2018.
//

#include "mesh.h"

/* Constructor */
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector <Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // Now that we have all of the required data, set the vertex buffers and its attribute pointers
    setupMesh();
}

/* Constructor */
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = {};
    // Now that we have all of the required data, set the vertex buffers and its attribute pointers
    setupMesh();
}

Mesh::Mesh(Primitive *primitive)
{
    this->vertices = primitive->getVertices();
    this->indices = primitive->getIndices();
    this->textures = {};
    // Now that we have all of the required data, set the vertex buffers and its attribute pointers
    setupMesh();
}

Mesh::Mesh(Primitive *primitive, std::vector <Texture> textures)
{
    this->vertices = primitive->getVertices();
    this->indices = primitive->getIndices();
    this->textures = textures;
    // Now that we have all of the required data, set the vertex buffers and its attribute pointers
    setupMesh();
}

Mesh::Mesh(Primitive *primitive, Texture texture)
{
    this->vertices = primitive->getVertices();
    this->indices = primitive->getIndices();
    this->textures.push_back(texture);
    // Now that we have all of the required data, set the vertex buffers and its attribute pointers
    setupMesh();
}



void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);

    if(!textures.size())
    {
    	// TODO: Move this to a init function
        DEFAULT_TEXTURE = loadTexture("../resources/wood.png");
    }

}

// Render the mesh

void Mesh::Draw(Shader shader)
{
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
            // retrieve texture number (the N in diffuse_textureN)
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
			if(name != "")
			{
				// Set the sampler
//				shader.setFloat(("material." + name + number).c_str(), i);
//				std::cout << ( "material." + name + number).c_str() << std::endl;
				// Set the sampler
				shader.setFloat((name + number).c_str(), i);
			}
			// now set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // Bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
    }
    else
    {
        // If there are no textures, use default texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, DEFAULT_TEXTURE);

    }

    // Draw Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void Mesh::Draw(Shader shader, unsigned int depthMap)
{
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
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer GLuint to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer GLuint to stream
			else if (name == "texture_height")
			{
				number = std::to_string(heightNr++); // transfer GLuint to stream
				shader.setFloat("heightScale", 0.1f);
			}
			if(name != "")
			{
				// Set the sampler
				shader.setInt((name).c_str(), i);
			}

			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
	}
	else
	{
		// If there are no textures, use default texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, DEFAULT_TEXTURE);

	}
	// DO SHADOW MAP TEXTURE HERE
	glActiveTexture(GL_TEXTURE1 + textures.size());
	shader.setInt("depthMap", textures.size() + 1);

	// TODO: Move this when I need to find another place for it
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);


	// Draw Mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Mesh::DrawCubeMap(Shader shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures[0].id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//FIXME: The crash probably lies here with my crappy pointers
unsigned int Mesh::getVAO(void)
{
    return this->VAO;
}

unsigned int Mesh::getDefaultTexture(void)
{
    return this->DEFAULT_TEXTURE;
}
