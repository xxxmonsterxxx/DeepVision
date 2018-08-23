#include "cylinder.h"

Cylinder::Cylinder(glm::vec3 pos_left, glm::vec3 pos_right, GLfloat radius, glm::vec3 color)
{
	this->color = color;

	glm::vec3 new_vec = pos_right - pos_left;

	float scalar = new_vec.x;

	float cosalpha = scalar / glm::length(new_vec);

	this->alpha_angle = glm::acos(cosalpha);
	this->move = glm::vec3((pos_left.x + pos_right.x)*0.5, (pos_left.y + pos_right.y)*0.5, (pos_left.z + pos_right.z)*0.5);

	axis = glm::cross(glm::vec3(1.f, 0.f, 0.f), new_vec);
	if (glm::length(axis) == 0)
	{
		axis = glm::vec3(1.0f, 0.f, 0.f);
		alpha_angle = 0;
	}

	this->size = glm::vec3(glm::length(pos_right - pos_left),radius, radius);
	
}
