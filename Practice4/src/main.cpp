#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define STB_IMAGE_IMPLEMENTATION

#include "GL/glew.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>
#include "../lib/shader.h"
#include "../lib/utils.h"
#include "../lib/vertex.h"
#include "../lib/buffer.h"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/texture.h"
#include "../lib/material.h"
#include "../lib/state.h"
#include "../lib/mesh.h"
#include "../lib/model.h"
#include "../lib/camera.h"
#include "../lib/world.h"
#include "../lib/light.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 1200

static bool Init()
{
	// init glew
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	State::defaultShader = std::make_shared<Shader>(readString("data/vertex.glsl").c_str(), readString("data/fragment.glsl").c_str());

    return true;
}

int main() {
///////////////////////////////////////////////////// OPENGL INIT ////////////////////////////////////////////////////////////////
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica 4", nullptr, nullptr);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create model
	std::shared_ptr<Model> GunslingerModel = std::make_shared<Model>(Mesh::load("data/gunslinger.obj"));
	GunslingerModel->setPosition(glm::vec3(0, 0, 0));
	GunslingerModel->setRotation(glm::vec3(0, -40, 0));
	GunslingerModel->setScale(glm::vec3(1, 1, 1));

	// Create camera
	std::shared_ptr<Camera> MainCamera = std::make_shared<Camera>();
	MainCamera->setPosition(glm::vec3(0, 0, 70));
	MainCamera->setRotation(glm::vec3(0, 0, 0));

	// Create directional light
	std::shared_ptr<Light> DirLight = std::make_shared<Light>(Light::Type::DIRECTIONAL, glm::vec3(1.f, 0.f, 0.f), 0.f);
	DirLight->setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	DirLight->setDiffuse(glm::vec3(0.f, 0.f, 0.f));
	DirLight->setSpecular(glm::vec3(0.f, 0.f, 0.f));
	DirLight->setPosition(glm::vec3(0.f, 10.f, 0.f));

	// Create positional light
	std::shared_ptr<Light> PointLight = std::make_shared<Light>(Light::Type::POINT, glm::vec3(0.f, 1.f, 0.f), 0.01f);
	PointLight->setAmbient(glm::vec3(0.f, 1.f, 0.f));
	PointLight->setDiffuse(glm::vec3(0.f, 1.f, 0.f));
	PointLight->setSpecular(glm::vec3(0.f, 1.f, 0.f));
	PointLight->setPosition(glm::vec3(3.f,0.f, 0.f));

	// Create world
	std::shared_ptr<World> MyWorld = std::make_shared<World>();
	MyWorld->addEntity(GunslingerModel);
	MyWorld->addEntity(MainCamera);
	MyWorld->addEntity(DirLight);
	MyWorld->addEntity(PointLight);
	MyWorld->setAmbient(glm::vec3(1.f, 1.f, 1.f));

	// main loop
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE)) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

		// Get Input
		if (glfwGetKey(win, GLFW_KEY_UP))
		{
            glm::vec3 forward = normalize(glm::vec3(State::viewMatrix[2])) * glm::vec3(1, 1, -1);
			MainCamera->move(forward * 10.f * deltaTime);
		}
		else if (glfwGetKey(win, GLFW_KEY_DOWN))
		{
			glm::vec3 forward = normalize(glm::vec3(State::viewMatrix[2])) * glm::vec3(1, 1, -1);
			MainCamera->move(-forward * 10.f * deltaTime);
		}
		else if (glfwGetKey(win, GLFW_KEY_LEFT))
		{
			MainCamera->move(glm::vec3(-10 * deltaTime, 0, 0));
		}
		else if (glfwGetKey(win, GLFW_KEY_RIGHT))
		{
			MainCamera->move(glm::vec3(10 * deltaTime, 0, 0));
		}

		if (glfwGetKey(win, GLFW_KEY_0))
		{
			DirLight->setAmbient(glm::vec3(1.f, 1.f, 1.f));
		}
		else if (glfwGetKey(win, GLFW_KEY_1))
		{
			DirLight->setAmbient(glm::vec3(1.f, 0.f, 0.f));
		}
		else if (glfwGetKey(win, GLFW_KEY_2))
		{
			DirLight->setAmbient(glm::vec3(0.f, 1.f, 0.f));
		}
		else if (glfwGetKey(win, GLFW_KEY_3))
		{
			DirLight->setAmbient(glm::vec3(0.f, 0.f, 1.f));
		}

		// Update main camera
		MainCamera->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));
		MainCamera->setProjection(glm::perspective<float>(glm::radians(45.0f), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 1, 1000));

		// Update
		MyWorld->update(deltaTime);

		// Draw
		MyWorld->draw();

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// Clean reserved memory
	MyWorld.reset();
	MainCamera.reset();
	PointLight.reset();
	DirLight.reset();
	GunslingerModel.reset();

	// shutdown
	glfwTerminate();
}