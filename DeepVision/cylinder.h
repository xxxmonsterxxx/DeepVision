#pragma once
#include "object.h"

class Cylinder : public Object
{
public:
	GLfloat alpha_angle;
	glm::vec3 axis;
	GLfloat radius;
	glm::vec3 move;

	Cylinder() : Object() {}
	Cylinder(glm::vec3 pos_left = glm::vec3(0.0f), glm::vec3 pos_right = glm::vec3(0.0f), GLfloat radius = 1, glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f));
};