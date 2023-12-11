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
#include "glm/glm.hpp"

namespace Engine {
	struct AppSettings {
		bool enableVsync;
		bool resizable;
		Vector2 windowSize;
		std::string title;
		Color clearColor;
		int glMajorVersion, glMinorVersion;

		AppSettings(): 
			enableVsync(true),
			resizable(true),
			windowSize(600, 600),
			title("Default Window"),
			clearColor(),
			glMajorVersion(3),
			glMinorVersion(3) {}
	};

	typedef std::function<void(std::shared_ptr<ResourceManager>)> ResourceFunc;
	typedef std::function<void(AppSettings&)> AppSettingsFunc;
	typedef std::function<void(Scene&)> SceneFunc;
	class App {
		private:
			std::shared_ptr<ResourceManager> resourceManager;
			Scene scene;
			RenderCtx ctx;
		private:
			ResourceFunc resourceFunc;
			AppSettingsFunc appSettingsFunc;
			SceneFunc sceneFunc;
		public:
			App(ResourceFunc, AppSettingsFunc, SceneFunc);
			~App();
			void Run();
		private:
			void RenderScene(Scene::Node*, RenderCtx&);
		private:
			GLFWwindow* NewWindow(const AppSettings&);
			GLFWwindow* GLFWInit(const AppSettings&);
	};
	void RunApp(
		std::function<void(std::weak_ptr<ResourceManager>)>,
		std::function<AppSettings(AppSettings)>,
		std::function<void(Scene&)>
	);
}

#endif
