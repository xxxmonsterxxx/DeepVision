#include "line.h"
#include <iostream>

Line::Line(glm::vec3 point1, glm::vec3 point2, glm::vec3 color)
{
	this->color = color;

	glm::vec3 new_vec = point2 - point1;

	float scalar = new_vec.x;

	float cosalpha = scalar / glm::length(new_vec);

	this->alpha_angle = glm::acos(cosalpha);
	this->move = glm::vec3(point1.x, point1.y, point1.z);

	axis = glm::cross(glm::vec3(1.f, 0.f, 0.f), new_vec);
	if (glm::length(axis) == 0)
	{
		axis = glm::vec3(1.0f, 0.f, 0.f);
		alpha_angle = 0;
	}
	this->size = glm::vec3(glm::length(point2 - point1), 1, 1);
}
