#include "object.h"

Object::Object()
	: position(0.0f, 0.0f, 0.0f), size(1.f, 1.f, 1.f), color(0.0f, 0.0f, 1.0f), velocity(0.0f, 0.0f, 0.0f) { }

Object::Object(glm::vec3 pos, glm::vec3 size, glm::vec3 color, glm::vec3 velocity)
	: position(pos), size(size), color(color), velocity(velocity) { }