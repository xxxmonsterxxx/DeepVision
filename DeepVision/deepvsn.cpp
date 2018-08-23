#include "deepvsn.h"
#include "resource_manager.h"
#include "sphere.h"
#include "cylinder.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DeepVision::DeepVision(GLuint width, GLuint height)
{
	// Load shaders
	ResourceManager::LoadShader("shaders/shader.vs", "shaders/shader.frag", nullptr, "shader");
	// Configure shaders

	this->renderer = new Renderer(ResourceManager::GetShader("shader"));
}

void DeepVision::addSphere(glm::vec3 position, GLfloat radius, glm::vec3 color)
{
	atoms.push_back(Sphere(position, glm::vec3(radius, radius, radius), color));
}

void DeepVision::addCylinder(glm::vec3 left, glm::vec3 right, GLfloat radius, glm::vec3 color)
{
	bonds.push_back(Cylinder(left, right, radius, color));
}

void DeepVision::callback()
{
	if (keys[0])
	{
		if (needupdate)
		{
			last_x = xmouse;
			last_y = ymouse;
			needupdate = GL_FALSE;
		}
		double dx = xmouse - last_x;
		double dy = ymouse - last_y;
		this->renderer->current_alpha += dx;
		this->renderer->current_betha += dy;
		last_x = xmouse;
		last_y = ymouse;
	}
	if (!keys[0])
		needupdate = GL_TRUE;
	this->renderer->zoom += offset * 0.1;
	offset = 0;
}

void DeepVision::render()
{
	for (Sphere &object : this->atoms)
		this->renderer->DrawObject(object);
	for (Cylinder &object : this->bonds)
		this->renderer->DrawObject(object);
}
