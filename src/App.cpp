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
		if (!w) {
			return nullptr;
		}
		return w;
	}

	void RunApp(std::function<AppSettings(AppSettings)> settingsFunc) {
		AppSettings settings = settingsFunc(AppSettings{});
		if (!glfwInit()) {
			spdlog::critical("glfwInit failed");
			exit(1);
		}
		GLFWwindow* w = NewWindow(settings);
		if (!w) {
			spdlog::critical("glfwCreateWindow failed");
			exit(1);
		}
		glfwMakeContextCurrent(w);

		while (!glfwWindowShouldClose(w)) {
			glfwPollEvents();
			glfwSwapBuffers(w);

		}

		glfwDestroyWindow(w);
	}
}
