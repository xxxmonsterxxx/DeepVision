#include "renderer.h"

// GLFW
#include <glfw3.h>

Renderer::Renderer(Shader &shader)
{
	this->shader = shader;

	initVertexDataSphere();
	initVertexDataCylind();
	initVertexDataLine();

	initGraphicalSettings(this->EBO_s, this->VBO_s, this->VAO_s, this->vertices_sphere, this->indices_sphere);
	initGraphicalSettings(this->EBO_c, this->VBO_c, this->VAO_c, this->vertices_cylind, this->indices_cylind);
	initGraphicalSettings(this->EBO_l, this->VBO_l, this->VAO_l, this->vertices_line, this->indices_line);
}

Renderer::~Renderer()
{
}

void Renderer::initVertexDataSphere()
{
	GLuint slices = 20, stacks = 20;
	// Calc The Vertices
	for (int i = 0; i <= slices; i++)
	{
		float phi = i * (glm::pi<float>() / slices);


		// Loop Through Slices
		for (int j = 0; j < stacks; j++)
		{
			float theta = j * (glm::pi <float>() * 2 / stacks);

			// Calc The Vertex Positions
			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices_sphere.push_back(glm::vec3(x, y, z));
		}
	}
	// Calc The Index Positions
	for (int i = 0; i < vertices_sphere.size() - stacks; i++)
	{
		if ((i + 1) % stacks == 0)
		{
			indices_sphere.push_back(i);
			indices_sphere.push_back(i - stacks + 1);
			indices_sphere.push_back(i + stacks);

			indices_sphere.push_back(i - stacks + 1);
			indices_sphere.push_back(i + stacks);
			if (i + 1 == vertices_sphere.size())
				indices_sphere.push_back(vertices_sphere.size() - stacks);
			else
				indices_sphere.push_back(i + 1);
		}
		else
		{
			indices_sphere.push_back(i);
			indices_sphere.push_back(i + 1);
			indices_sphere.push_back(i + stacks);

			indices_sphere.push_back(i + 1);
			indices_sphere.push_back(i + stacks);
			indices_sphere.push_back(i + stacks + 1);
		}
	}
}

void Renderer::initVertexDataCylind()
{
	GLuint slices = 20, stacks = 20;
	// Calc The Vertices
	for (int i = 0; i <= slices; i++)
	{
		float x = i * (1.f / slices) - 0.5f;
		// Loop Through Slices
		for (int j = 0; j < stacks; j++)
		{
			float theta = j * (glm::pi <float>() * 2 / stacks);

			// Calc The Vertex Positions
			float y = cosf(theta);
			float z = sinf(theta);

			// Push Back Vertex Data
			vertices_cylind.push_back(glm::vec3(x, y, z));
		}
	}
	// Calc The Index Positions
	for (int i = 0; i < vertices_cylind.size() - stacks; i++)
	{
		if ((i + 1) % stacks == 0)
		{
			indices_cylind.push_back(i);
			indices_cylind.push_back(i - stacks + 1);
			indices_cylind.push_back(i + stacks);

			indices_cylind.push_back(i - stacks + 1);
			indices_cylind.push_back(i + stacks);
			if (i + 1 == vertices_cylind.size())
				indices_cylind.push_back(vertices_cylind.size() - stacks);
			else
				indices_cylind.push_back(i + 1);
		}
		else
		{
			indices_cylind.push_back(i);
			indices_cylind.push_back(i + 1);
			indices_cylind.push_back(i + stacks);

			indices_cylind.push_back(i + 1);
			indices_cylind.push_back(i + stacks);
			indices_cylind.push_back(i + stacks + 1);
		}
	}
}

void Renderer::initVertexDataLine()
{
	vertices_line.push_back(glm::vec3(0.f));
	vertices_line.push_back(glm::vec3(1.f, 0.f, 0.f));

	indices_line.push_back(0);
	indices_line.push_back(1);
}

void Renderer::initGraphicalSettings(GLuint &EBO, GLuint &VBO, GLuint &VAO, std::vector<glm::vec3> vertices, std::vector<GLuint> indices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat) * 3, glm::value_ptr(vertices[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::DrawObject(Sphere &sphere)
{
	// Prepare transformations
	this->shader.Use();

	// Create transformations
	
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, zoom - 10.f));
	view = glm::rotate(view, (GLfloat)(current_betha), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, (GLfloat)(current_alpha), glm::vec3(.0f, 1.0f, 0.0f));
	glm::mat4 projection;
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	glm::mat4 model;
	model = glm::translate(model, sphere.position);
	model = glm::scale(model, sphere.size);

	this->shader.SetMatrix4("model", model);
	this->shader.SetMatrix4("view", view);
	this->shader.SetMatrix4("projection", projection);

	// Render textured quad
	this->shader.SetVector3f("myColor", sphere.color);

	glBindVertexArray(this->VAO_s);
	glDrawElements(GL_TRIANGLES, this->indices_sphere.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::DrawObject(Cylinder &cylind)
{
	// Prepare transformations
	this->shader.Use();


	// Create transformations

	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.f, zoom - 10.f));
	view = glm::rotate(view, (GLfloat)(current_betha), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, (GLfloat)(current_alpha), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection;
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	glm::mat4 model;
	model = glm::translate(model, cylind.move);
	model = glm::rotate(model, glm::degrees(cylind.alpha_angle), cylind.axis);
	model = glm::scale(model, cylind.size);
	


	this->shader.SetMatrix4("model", model);
	this->shader.SetMatrix4("view", view);
	this->shader.SetMatrix4("projection", projection);

	// Render textured quad
	this->shader.SetVector3f("myColor", cylind.color);

	glBindVertexArray(this->VAO_c);
	glDrawElements(GL_TRIANGLES, this->indices_cylind.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::DrawObject(Line &line)
{
	// Prepare transformations
	this->shader.Use();


	// Create transformations

	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.f, zoom - 1.f));
	view = glm::rotate(view, (GLfloat)(current_betha), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, (GLfloat)(current_alpha), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection;
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	glm::mat4 model;
	model = glm::translate(model, line.move);
	model = glm::rotate(model, glm::degrees(line.alpha_angle), line.axis);
	model = glm::scale(model, line.size);
	

	this->shader.SetMatrix4("model", model);
	this->shader.SetMatrix4("view", view);
	this->shader.SetMatrix4("projection", projection);

	// Render textured quad
	this->shader.SetVector3f("myColor", line.color);


	glBindVertexArray(this->VAO_l);
	glLineWidth(5);
	glDrawElements(GL_LINE_STRIP, sizeof(indices_line) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
