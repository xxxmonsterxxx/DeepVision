#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>

#include "deepvsn.h"
#include "data_manager.h"

#include <string>
#include <iostream>


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

DeepVision *widget;

void main()
{
	std::string rscr = "resources/";
	std::string wfn_name, cpt_name;

	std::cout << "Welcome to Deep Vision(c)\
		\nMolecular visualisator for data by \"TWOe\"\
		\nFor more info pls read \"Readme\"\
		\nEnter pls names of .wfn and .cpt files... \n";
	std::cin >> wfn_name >> cpt_name;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Deep Vision", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	Data_Manager dt_mng;
	dt_mng.load_data((rscr + wfn_name).c_str(), (rscr + cpt_name).c_str());

	widget = new DeepVision();
	dt_mng.draw(widget);

	while (!glfwWindowShouldClose(window))
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glfwPollEvents();
		// Manage user input
		widget->callback();
		// Render
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //Background color
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		widget->render();

		glfwSwapBuffers(window);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	/*if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}*/
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	widget->xmouse = xpos;
	widget->ymouse = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			widget->keys[0] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			widget->keys[0] = GL_FALSE;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
			widget->keys[1] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			widget->keys[1] = GL_FALSE;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	widget->offset = yoffset;
}
