#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GL/glew.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>
#include "../lib/shader.h"
#include "../lib/utils.h"
#include "../lib/vertex.h"
#include "../lib/buffer.h"
#include "../lib/glm/gtc/matrix_transform.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

bool Init()
{
	// init glew
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	return true;
}

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica 1", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);


	if (!Init())
	{
		std::cout << "could not initialize glew" << std::endl;
		return -1;
	}


	Shader* shader = new Shader(readString("data/vertex.glsl").c_str(), readString("data/fragment.glsl").c_str());
	shader->use();

	std::vector<Vertex> vertices = {
	    Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(0.5f, -0.5f, 0), glm::vec3(0, 0, 1))
    };

	std::vector<uint16_t> indices = { 0, 1, 2 };

	Buffer* buffer = new Buffer(vertices, indices);

	// main loop
	float angle = 0;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		glViewport(0, 0, screenWidth, screenHeight);
		glScissor(0, 0, screenWidth, screenHeight);

		// Projection matrix
		glm::mat4 proj = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 1, 1000);

		// View matrix
		glm::mat4 view = glm::lookAt<float>(glm::vec3(0, 0, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		// Clean color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		for (int x = -3; x <= 3; x+=3)
		{
		    for (int z = 0; z >= -6; z-=3)
		    {
		        // Model matrix
		        glm::mat4 model = glm::translate<float>(glm::mat4(), glm::vec3(x, 0, z));
		        model = glm::rotate<float>(model, glm::radians(angle), glm::vec3(0, 1, 0));

				//Set MVP
		        shader->setMatrix(shader->getLocation("mvp"), proj * view * model);

				// Draw
		        buffer->draw(*shader);
		    }
		}

		// Update angle
		angle += 32 * deltaTime;

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// Clean reserved memory
	delete buffer;
	vertices.clear();
	indices.clear();
	delete shader;

	// shutdown
	glfwTerminate();
}