//
// Created by Sean on 8/8/2019.
//

#include <iterator>
#include "Scene.h"
#include <GLFW/glfw3.h>

// Max light definitions
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10
#define MAX_DIR_LIGHTS 10

Scene::Scene()
{
	this->m_num_point_lights = 0;
	this->m_num_dir_lights = 0;
	this->m_num_spot_lights = 0;

	// Default camera
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	this->m_cameras.push_back(camera);
	setDefaultCamera(0);
}



void Scene::addEntity(std::shared_ptr<Entity> targetEntity)
{
	this->m_entities.push_back(targetEntity);
}

void Scene::addLight(std::shared_ptr<Light> targetLight)
{
	if(typeid(*targetLight) == typeid(DirectionalLight))
	{
		if(this->m_num_dir_lights < MAX_DIR_LIGHTS)
		{
			m_num_dir_lights++;
			std::cout << "dir light added" << std::endl;
		}
		else
		{
			std::cout << "Max dir light limit hit" << std::endl;
		}
	}
	else if(typeid(*targetLight) == typeid(PointLight))
	{
		if(this->m_num_point_lights < MAX_DIR_LIGHTS)
		{
			m_num_point_lights++;
			std::cout << "point light added" << std::endl;
		}
		else
		{
			std::cout << "Max point light limit hit" << std::endl;
		}
	}
	else if(typeid(*targetLight) == typeid(SpotLight))
	{
		if(this->m_num_spot_lights < MAX_DIR_LIGHTS)
		{
			m_num_spot_lights++;
			std::cout << "spot light added" << std::endl;
		}
		else
		{
			std::cout << "Max spot light limit hit" << std::endl;
		}
	}
	else
	{
		std::cout << "not a known light type!" << std::endl;
	}
	this->m_lights.push_back(targetLight);
}

void Scene::addCamera(void)
{
	//this->m_cameras.push_back(std::unique_ptr<Camera>);
}


// TODO: Clean up this function (scene should not own render -> buffer manipulation belongs in renderer)
void Scene::render(Shader *shader, BufferObject *buffer)
{
	if(this->m_active)
	{
		glm::mat4 view = this->m_default_camera->GetViewMatrix();
//		shader->setMat4("projection", buffer->getProjection());
		// TODO: Framebuffer has to be decoupled from scene
		shader->use();
		setShaderPointLights(shader);
		setShaderDirLights(shader);
		setShaderSpotLights(shader);
		shader->setMat4("view", view);

		// TODO: Move this to a function
		shader->setFloat("material.shininess", 1.0f);

		// TODO: Move this to a separate function
		// TODO: Allow for multiple cameras
		shader->setVec3("viewPos", this->m_default_camera->Position);

		buffer->bind(view);

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->render(shader);
		}

		for (int i = 0; i < m_lights.size(); i++)
		{
			m_lights[i]->render(shader);
		}
		buffer->unbind();
	}
}

glm::vec3 lightPos(-5.0f, 1.0f, -1.0f);

void Scene::renderWithShadows(Shader *shader, Shader *shadowShader, BufferObject *buffer, BufferObject *shadowBuffer)
{
	if(this->m_active)
	{
		const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

		lightPos.x = 1 + sin(glfwGetTime()) * 300.0f;
		lightPos.z = cos(glfwGetTime()) * 2.0f;
		lightPos.y = 1.0 + cos(glfwGetTime()) * 1.0f;
		// 1. Render Depth of scene to texture (from lights perspective)
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0, far_plane = 1000.5f;
//		lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
		// note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		// Render scene from light's point of view


		glm::mat4 view = this->m_default_camera->GetViewMatrix();

		// TODO: Allow for multiple lights with shaders
		// Shadow Section
		shadowShader->use();
		shadowShader->use();
		shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
		shadowBuffer->bind(view);

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->render(shadowShader);
		}
		shadowBuffer->unbind();

		// Not shadow Section
//		shader->setMat4("projection", buffer->getProjection());
		// TODO: Framebuffer has to be decoupled from scene
		shader->use();
		shader->use();
		shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
		shader->setVec3("lightPos", lightPos);
		shader->setMat4("projection", buffer->getProjection());
		setShaderPointLights(shader);
		setShaderDirLights(shader);
		setShaderSpotLights(shader);
		shader->setMat4("view", view);

		// TODO: Move this to a function
		shader->setFloat("material.shininess", 1.0f);

		// TODO: Move this to a separate function
		// TODO: Allow for multiple cameras
		shader->setVec3("viewPos", this->m_default_camera->Position);

		buffer->bind(view);

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->render(shader, shadowBuffer->getTextureBuffer());
		}

		for (int i = 0; i < m_lights.size(); i++)
		{
			m_lights[i]->render(shader);
		}
		buffer->unbind();
	}
}
void Scene::setActiveScene(void)
{
	this->m_active = true;
}
void Scene::setInactiveScene(void)
{
	this->m_active = false;
}

void Scene::setNumberOfPointLights(int numLights)
{
	this->m_num_point_lights = numLights;
}
void Scene::setNumberOfDirLights(int numLights)
{
	this->m_num_dir_lights = numLights;
}
void Scene::setNumberOfSpotLights(int numLights)
{
	this->m_num_spot_lights = numLights;
}
void Scene::setShaderPointLights(Shader *shader)
{
	shader->setInt("u_num_point_lights", m_num_point_lights);
}
void Scene::setShaderDirLights(Shader *shader)
{
	shader->setInt("u_num_dir_lights", m_num_dir_lights);
}
void Scene::setShaderSpotLights(Shader *shader)
{
	shader->setInt("u_num_spot_lights", m_num_spot_lights);
}

void Scene::setDefaultCamera(int cameraNum)
{
	if(cameraNum < this->m_cameras.size())
	{
		m_default_camera = std::make_shared<Camera>(this->m_cameras[cameraNum]);
	}
}


std::shared_ptr<Camera> Scene::getDefaultCamera(void)
{
	return m_default_camera;
}



std::shared_ptr<Entity> Scene::getEntityByID(std::string targetID)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID == targetID)
		{
			return m_entities[i];
		}
	}
	return m_entities[0];
}
std::shared_ptr<Light> Scene::getLightByID(std::string targetID)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			return m_lights[i];
		}
	}

	return m_lights[0];
}


void Scene::setLightPosition(std::string targetID, glm::vec3 targetPosition)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			m_lights[i]->updatePosition(targetPosition);
			return;
		}
	}
}


void Scene::setLightDirection(std::string targetID, glm::vec3 targetDirection)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			m_lights[i]->updateDirection(targetDirection);
			return;
		}
	}
}

void Scene::toggleLight(std::string targetID, bool toggle)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		if(m_lights[i]->m_ID == targetID)
		{
			m_lights[i]->toggle(toggle);
			return;
		}
	}
}

// TODO: Figure out why this is not working

void Scene::setEntityPosition(std::string targetID, glm::vec3 targetPosition)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID.compare(targetID) == 0)
		{
			m_entities[i]->setPosition(targetPosition);
			return;
		}
	}
}
void Scene::setEntityRotationDeg(std::string targetID, float targetRotAngle, glm::vec3 targetRotation)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID == targetID)
		{
			m_entities[i]->setRotation(targetRotAngle, targetRotation);
			return;
		}
	}
}

void Scene::setEntityScale(std::string targetID, glm::vec3 targetScale)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_ID == targetID)
		{
			m_entities[i]->setScale(targetScale);
			return;
		}
	}
}





std::vector<std::string> Scene::showSceneDetails(void)
{
	std::vector<std::string> returnString;
	for (int i = 0; i < m_entities.size(); i++)
	{
		std::string info;
		info = m_entities[i]->m_ID + ": " +
				"\nPosition: " +glm::to_string(m_entities[i]->getPosition()) +
				"\nRotation: " +glm::to_string(m_entities[i]->getRotation()) +
				"\nScale:	 " +glm::to_string(m_entities[i]->getScale());
		returnString.push_back(info);
	}
	for (int i = 0; i < m_lights.size(); i++)
	{
		std::string info;
		info = m_lights[i]->m_ID + ": " +
			   "\nPosition: " +glm::to_string(m_lights[i]->getPosition()) +
			   "\nDirection: " +glm::to_string(m_lights[i]->getDirection());
		returnString.push_back(info);
	}
	return returnString;
}