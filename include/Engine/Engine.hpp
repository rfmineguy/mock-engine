#ifndef ENGINE_H
#define ENGINE_H
#include "RenderCtx.hpp"
#include <functional>

namespace Engine {
	template <typename T>
	void NewEntity(const std::string&, std::function<void(T&)>, std::function<void(T&, double)>, std::function<void(T&, RenderCtx&)>);
}

#endif
