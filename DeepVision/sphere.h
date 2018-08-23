#pragma once

#include "object.h"

class Sphere : public Object
{
public:
	Sphere() : Object() {}
	Sphere(glm::vec3 pos, glm::vec3 size = glm::vec3(1, 1, 1), glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f))
		: Object(pos, size, color, velocity) {}
};