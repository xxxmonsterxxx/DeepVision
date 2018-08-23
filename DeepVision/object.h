#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


class Object
{
public:
	// Object state
	glm::vec3 position, size, velocity, color;
	// Render state
	// Constructor(s)
	Object();
	Object(glm::vec3 pos, glm::vec3 size = glm::vec3(1, 1, 1), glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f));
};	