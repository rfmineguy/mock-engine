#ifndef APP_H
#define APP_H
#include <functional>

namespace Engine {
	struct AppSettings {
		int targetFPS;
		bool resizable;
	};

	void RunApp(std::function<void(AppSettings&)>);
}

#endif
