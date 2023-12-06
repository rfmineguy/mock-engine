#ifndef APP_H
#define APP_H
#include "Engine/RenderCtx.hpp"
#include "Engine/Vector.hpp"
#include "Engine/Color.hpp"
#include <functional>
#include <string>

namespace Engine {
	struct AppSettings {
		int targetFPS;
		bool resizable;
		Vector2 windowSize;
		std::string title;
		Color clearColor;

		AppSettings(): targetFPS(30), resizable(true), windowSize(600, 600), title("Default Window"), clearColor() {}
	};

	struct Scene {
		template <typename T>
		void AddEntity(
			const std::string& id,
			std::function<void (T&)> start,
			std::function<void (T &, double)> update,
			std::function<void (T &, RenderCtx &)> render); 
	};

	void RunApp(std::function<AppSettings(AppSettings)>, std::function<Scene(Scene)>);
}

#endif
