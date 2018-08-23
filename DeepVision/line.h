#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Line
{
private:
	glm::vec3 point1;
	glm::vec3 point2;
public:
	GLfloat alpha_angle;
	glm::vec3 axis;
	glm::vec3 move, size, color;

	Line(glm::vec3 point1 = glm::vec3(0.f), glm::vec3 point2 = glm::vec3(1.0f, 0.f, 0.f), glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.f));
};