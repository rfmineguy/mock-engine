#include "Engine/App.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/Logger.hpp"
#include "glad/glad.h"
#include "spdlog.h"

namespace Engine {
	App::App(ResourceFunc resFunc, AppSettingsFunc settingsFunc, SceneFunc sceneFunc)
	: resourceFunc(resFunc), appSettingsFunc(settingsFunc), sceneFunc(sceneFunc) {}
	
	App::~App() {
		
	}

	GLFWwindow* App::NewWindow(const AppSettings& settings) {
		glfwWindowHint(GLFW_RESIZABLE, settings.resizable ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		GLFWwindow* w = glfwCreateWindow(
			settings.windowSize.x, settings.windowSize.y, settings.title.c_str(), nullptr, nullptr
		);
		return w;
	}

	GLFWwindow* App::GLFWInit(const AppSettings& settings) {
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
		spdlog::info("Created glfw window");
		return w;
	}

	void App::Run() {
		// Get app settings
		AppSettings settings = AppSettings{};
		appSettingsFunc(settings);
		GLFWwindow* w = GLFWInit(settings);

		// Load glad
		int version = gladLoadGL();
		spdlog::info("Glad GL version {}", version);
		
		// glad required for this
		resourceFunc(resourceManager);

		// load scene
		sceneFunc(scene);
		
		// Main loop ...
		double t, fps;
		double t0 = glfwGetTime();
		double deltaTime = 0;

		int frameCount = 0;
		while (!glfwWindowShouldClose(w)) {
			glClearColor(settings.clearColor.r / 255.f, settings.clearColor.g / 255.f, settings.clearColor.b / 255.f, settings.clearColor.a / 255.f);
			glClear(GL_COLOR_BUFFER_BIT);
			// render here
			/* 1. Traverse the scene heirarchy somehow
			 * 2. Accumulate the translation as we traverse so it appears that a parent/child relationship exists
			 * 3. Batch what each entity renders (FUTURE)
			 */

			// calculate fps
			t = glfwGetTime();
			if ((t - t0) > 1.0 || frameCount == 0) {
				fps = (double) frameCount / (t - t0);
				glfwSetWindowTitle(w, (settings.title + std::to_string(fps) + ":" + std::to_string(deltaTime)).c_str());
				deltaTime = t - t0;
				t0 = t;
				frameCount = 0;
				// spdlog::info("Resource pool. {}", Engine::Internal::ResourceManager::resources().size());
			}
			frameCount++;

			glfwSwapBuffers(w);
			glfwPollEvents();
		}

		// Engine::FreeResources();
		glfwDestroyWindow(w);
		glfwTerminate();

	}
}
