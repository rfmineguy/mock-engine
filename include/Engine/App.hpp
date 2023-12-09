#ifndef APP_H
#define APP_H
#include "Engine/RenderCtx.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/Vector.hpp"
#include "Engine/Color.hpp"
#include "Engine/Scene.hpp"
#include <functional>
#include <string>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Engine {
	struct AppSettings {
		int targetFPS;
		bool resizable;
		Vector2 windowSize;
		std::string title;
		Color clearColor;

		AppSettings(): targetFPS(30), resizable(true), windowSize(600, 600), title("Default Window"), clearColor() {}
	};

	typedef std::function<void(ResourceManager&)> ResourceFunc;
	typedef std::function<void(AppSettings&)> AppSettingsFunc;
	typedef std::function<void(Scene&)> SceneFunc;
	class App {
		private:
			ResourceManager resourceManager;
			Scene scene;
		private:
			ResourceFunc resourceFunc;
			AppSettingsFunc appSettingsFunc;
			SceneFunc sceneFunc;
		public:
			App(ResourceFunc, AppSettingsFunc, SceneFunc);
			~App();
			void Run();
		private:
			GLFWwindow* NewWindow(const AppSettings&);
			GLFWwindow* GLFWInit(const AppSettings&);
	};
	void RunApp(
			std::function<void(ResourceManager&)>,
			std::function<AppSettings(AppSettings)>,
			std::function<void(Scene&)>
			);
}

#endif
