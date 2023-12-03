#ifndef APP_H
#define APP_H
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
	};

	void RunApp(std::function<AppSettings(AppSettings)>);
}

#endif
