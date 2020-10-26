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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

// Box Model Update function
void UpdateBoxModel(Model& model, float deltaTime)
{
	// Update angle
	model.setRotation(model.getRotation() + glm::vec3(0, 32 * deltaTime, 0));
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
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica 2", nullptr, nullptr);
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

	std::vector<Vertex> vertices = {
		// lateral frontal
	    Vertex(glm::vec3(-0.5f, 0.5f, 0.5), glm::vec3(1, 0, 0), glm::vec2(0, 1)),		// v0
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5), glm::vec3(0, 1, 0), glm::vec2(0, 0)),	// v1
		Vertex(glm::vec3(0.5f, -0.5f, 0.5), glm::vec3(0, 0, 1), glm::vec2(1, 0)),		// v2
		Vertex(glm::vec3(0.5f, 0.5f, 0.5), glm::vec3(0, 0, 1), glm::vec2(1, 1)),		// v3
		// lateral derecho
	    Vertex(glm::vec3(0.5f, 0.5f, 0.5), glm::vec3(0, 0, 1), glm::vec2(0, 1)),		// v4
		Vertex(glm::vec3(0.5f, -0.5f, 0.5), glm::vec3(0, 0, 1), glm::vec2(0, 0)),		// v5
		Vertex(glm::vec3(0.5f, -0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(1, 0)),	// v6
		Vertex(glm::vec3(0.5f, 0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(1, 1)),		// v7
		// lateral trasero
		Vertex(glm::vec3(0.5f, 0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(0, 1)),		// v8
		Vertex(glm::vec3(0.5f, -0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(0, 0)),	// v9
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(1, 0)),	// v10
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(1, 1)),	// v11
		// lateral izquierdo
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(0, 1)),	// v12
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(0, 0)),	// v13
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),	// v14
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5), glm::vec3(1, 0, 0), glm::vec2(1, 1))		// v15
    };

	std::vector<uint16_t> indices = {
	    0, 1, 2,
	    0, 2 ,3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15
	};

	std::vector<Vertex> verticesTapas = {
		// Tapa superior
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(1, 0)),	// v0
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5), glm::vec3(1, 0, 0), glm::vec2(0, 0)),		// v1
		Vertex(glm::vec3(0.5f, 0.5f, 0.5), glm::vec3(0, 0, 1), glm::vec2(0, 1)),		// v2
		Vertex(glm::vec3(0.5f, 0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(1, 1)),		// v3
		// Tapa inferior
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),	// v4
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(0, 0)),	// v5
		Vertex(glm::vec3(0.5f, -0.5f, -0.5), glm::vec3(0, 0, 1), glm::vec2(0, 1)),	// v6
		Vertex(glm::vec3(0.5f, -0.5f, 0.5), glm::vec3(0, 0, 1), glm::vec2(1, 1))		// v7
	};

	std::vector<uint16_t> indicesTapas = {
		0, 1, 2,
		0, 2 ,3,
		4, 5, 6,
		4, 6, 7
	};

	// Load textures and create mesh from buffers
	std::shared_ptr<Mesh> BoxMesh = std::make_shared<Mesh>();
	BoxMesh->addBuffer(std::make_shared<Buffer>(vertices, indices), Material(Texture::load("data/front.png"), State::defaultShader));
	BoxMesh->addBuffer(std::make_shared<Buffer>(verticesTapas, indicesTapas), Material(Texture::load("data/top.png"), State::defaultShader));

	// Create model
	std::shared_ptr<Model> BoxModel = std::make_shared<Model>(BoxMesh);
	BoxModel->setCallbackFunc(UpdateBoxModel);

	// Create camera
	std::shared_ptr<Camera> MainCamera = std::make_shared<Camera>();
	MainCamera->setPosition(glm::vec3(0, 0, 3));
	MainCamera->setRotation(glm::vec3(-20, 0, 0));

	// Create world
	std::shared_ptr<World> MyWorld = std::make_shared<World>();
	MyWorld->addEntity(BoxModel);
	MyWorld->addEntity(MainCamera);

	// main loop
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE)) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

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
	BoxModel.reset();
	BoxMesh.reset();
	vertices.clear();
	indices.clear();

	// shutdown
	glfwTerminate();
}