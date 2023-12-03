#include "Engine/App.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog.h"

namespace Engine {
	GLFWwindow* NewWindow(const AppSettings& settings) {
		glfwWindowHint(GLFW_RESIZABLE, settings.resizable ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		GLFWwindow* w = glfwCreateWindow(
			settings.windowSize.x, settings.windowSize.y, settings.title.c_str(), nullptr, nullptr
		);
		return w;
	}

	GLFWwindow* SetupGLFW(const AppSettings& settings) {
		if (!glfwInit()) {
			spdlog::critical("glfwInit failed - closing application");
			glfwTerminate();
			exit(1);
		}
		spdlog::info("Initialized glfw");
		GLFWwindow* w = NewWindow(settings);
		if (!w) {
			spdlog::critical("glfwCreateWindow failed - closing application");
			exit(1);
		}
		glfwMakeContextCurrent(w);
		return w;
	}

	/**
	 *    Main loop for application
	 *    	1. Handles events
	 *    	2. Window management
	 */
	void RunApp(std::function<AppSettings(AppSettings)> settingsFunc) {
		if (settingsFunc == nullptr) {
			spdlog::critical("Missing settings");
			exit(1);
		}

		// Setup/Initialization ...
		AppSettings settings = settingsFunc(AppSettings{});
		GLFWwindow* w = SetupGLFW(settings);
		spdlog::info("Initialized window");

		int version = gladLoadGL();
		spdlog::info("Initialized glad");

		// Main loop ...
		while (!glfwWindowShouldClose(w)) {
			glClearColor(settings.clearColor.r / 255.f, settings.clearColor.g / 255.f, settings.clearColor.b / 255.f, settings.clearColor.a / 255.f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwPollEvents();
			glfwSwapBuffers(w);
		}

		// Teardown/Deinitialization ...
		glfwDestroyWindow(w);
		glfwTerminate();
	}
}