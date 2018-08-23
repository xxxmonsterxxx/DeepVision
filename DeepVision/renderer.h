#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "sphere.h"
#include "cylinder.h"
#include "line.h"


class Renderer
{
public:
	// Constructor (inits shaders/shapes)
	Renderer(Shader &shader);

	void DrawObject(Sphere &sphere);
	void DrawObject(Cylinder &cylind);
	void DrawObject(Line &line);

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

	std::vector<glm::vec3>	vertices_line;
	std::vector<GLuint>		indices_line;

	void initVertexDataSphere();
	void initVertexDataCylind();
	void initVertexDataLine();

	void initGraphicalSettings(GLuint &EBO, GLuint &VBO, GLuint &VAO, std::vector<glm::vec3> vertices, std::vector<GLuint> indices);

	GLuint VAO_s, VAO_c, VAO_l;
	GLuint EBO_s, EBO_c, EBO_l;
	GLuint VBO_s, VBO_c, VBO_l;
};
