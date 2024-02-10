#include "Engine/App.hpp"
#include "Engine/Entity.hpp"
#include "Engine/RenderCtx.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/Logger.hpp"
#include "Engine/Engine.hpp"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "spdlog.h"

namespace Engine {
	class RootEntity : public Engine::IEntity {
		public:
			RootEntity(): IEntity("root") {}
			~RootEntity() {}
			void Start() override {}
			void Update(double dt) override {}
			void Render(RenderCtx& ctx) const override {}
	};

	App::App(ResourceFunc resFunc, AppSettingsFunc settingsFunc, SceneFunc sceneFunc)
	: resourceFunc(resFunc), appSettingsFunc(settingsFunc), sceneFunc(sceneFunc), resourceManager(std::make_shared<ResourceManager>()) {}
	
	App::~App() {}

	GLFWwindow* App::NewWindow(const AppSettings& settings) {
		glfwWindowHint(GLFW_RESIZABLE, settings.resizable ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.glMinorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.glMajorVersion);
		glfwSwapInterval(settings.enableVsync ? 1 : 0);
		GLFWwindow* w = glfwCreateWindow(
			settings.windowSize.x, settings.windowSize.y, settings.title.c_str(), nullptr, nullptr
		);
		glfwSetWindowUserPointer(w, this);
		glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);
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
	void App::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		App* app = (App*) glfwGetWindowUserPointer(window);
		app->currentAppSettings.windowSize = glm::vec2(width, height);
		app->ctx.UpdateSize(width, height);
		glViewport(0, 0, width, height);
		spdlog::info("{}x{}", width, height);
	}

	void App::Run() {
		// Run some preliminary initialization
		Engine::Init();

		// Get app settings
		AppSettings settings = AppSettings{};
		appSettingsFunc(settings);
		currentAppSettings = settings;
		GLFWwindow* w = GLFWInit(settings);

		// Load glad
		int version = gladLoadGL();
		spdlog::info("Glad GL version {}", version);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		
		// glad required for this
		resourceFunc(resourceManager);
		ctx.Init();
		ctx.UpdateSize(settings.windowSize.x, settings.windowSize.y);

		//
		// NOTE: The start function for entities is called when they are added to the scene heirarchy
		//

		// load scene
		sceneRoot = new RootEntity();
		sceneFunc(sceneRoot);
		
		// Main loop ...
		double t, fps;
		double t0 = glfwGetTime();
		double currentFrame = glfwGetTime();
		double lastFrame = 0;
		deltaTime = currentFrame - lastFrame;

		int frameCount = 0;
		while (!glfwWindowShouldClose(w)) {
			glClearColor(settings.clearColor.r / 255.f, settings.clearColor.g / 255.f, settings.clearColor.b / 255.f, settings.clearColor.a / 255.f);
			glClear(GL_COLOR_BUFFER_BIT);
			// render here
			/* 1. Traverse the scene heirarchy somehow
			 * 2. Accumulate the translation as we traverse so it appears that a parent/child relationship exists
			 * 3. Batch what each entity renders (FUTURE)
			 */

			RenderScene(sceneRoot, ctx);

			// calculate fps
			t = glfwGetTime();
			if ((t - t0) > 1.0 || frameCount == 0) {
				fps = (double) frameCount / (t - t0);
				glfwSetWindowTitle(w, (settings.title + std::to_string(fps) + ":" + std::to_string(deltaTime)).c_str());
				deltaTime = t - t0;
				t0 = t;
				frameCount = 0;
			}
			frameCount++;

			glfwSwapBuffers(w);
			glfwPollEvents();
		}

		glfwDestroyWindow(w);
		glfwTerminate();
	}

	// NOTE: What if we keep track of the transformation via the RenderCtx?
	void App::RenderScene(IEntity* node, RenderCtx& ctx) {
		if (node == nullptr) {}
		else {
			// Render node. RenderCtx transformation will be updated here
			if (!node->resourceManager) node->resourceManager = resourceManager; 
			node->Update(deltaTime);
			node->Render(ctx);
		}

		for (auto* n : node->children) {
			const bool DEBUG_PRINT = false;
			ctx.Push(DEBUG_PRINT ? n->GetID() : "");
			RenderScene(n, ctx);
			ctx.Pop(DEBUG_PRINT ? n->GetID() : "");
		}
	}
}
