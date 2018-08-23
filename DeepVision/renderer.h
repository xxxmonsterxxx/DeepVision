#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "sphere.h"
#include "cylinder.h"


class Renderer
{
public:
	// Constructor (inits shaders/shapes)
	Renderer(Shader &shader);

	void DrawObject(Sphere &sphere);
	void DrawObject(Cylinder &cylind);

	double current_alpha = -50, current_betha = -20;
	double zoom = 0;

	// Destructor
	~Renderer();
private:
	// Render state
	Shader shader;

	std::vector<glm::vec3>	vertices_sphere;
	std::vector<GLuint>		indices_sphere;

	std::vector<glm::vec3>	vertices_cylind;
	std::vector<GLuint>		indices_cylind;

	void initVertexDataSphere();
	void initVertexDataCylind();

	void initGraphicalSettings(GLuint &EBO, GLuint &VBO, GLuint &VAO, std::vector<glm::vec3> vertices, std::vector<GLuint> indices);

	GLuint VAO_s, VAO_c;
	GLuint EBO_s, EBO_c;
	GLuint VBO_s, VBO_c;
};
