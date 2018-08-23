#pragma once

#include "sphere.h"
#include "cylinder.h"
#include "renderer.h"

#include <vector>


class DeepVision
{
private:
	Renderer *renderer;
	GLuint width, height;

public:
	GLboolean keys[2];

	// mouse drag input callback parameters
	GLboolean needupdate = GL_TRUE; // update for start drag mouse pos
	double xmouse, ymouse;
	double last_x, last_y;

	// mouse wheel input callback
	double offset;

	std::vector<Sphere> atoms;
	std::vector<Cylinder> bonds;

	DeepVision(GLuint width = 800, GLuint height = 600);

	void addSphere(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), GLfloat radius = 1, glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f));
	void addCylinder(glm::vec3 left, glm::vec3 right, GLfloat radius = 1, glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f));

	void callback();
	void render();
};