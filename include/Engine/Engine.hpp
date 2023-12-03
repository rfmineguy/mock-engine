#ifndef ENGINE_H
#define ENGINE_H
#include "RenderCtx.hpp"
#include <functional>
#include <iostream>
#include "spdlog.h"

namespace Engine {
	template <typename T>
	void NewEntity(const std::string&, std::function<void(T&)>, std::function<void(T&, double)>, std::function<void(T&, RenderCtx&)>);
}

template <typename T>
void Engine::NewEntity(
		const std::string& id,
		std::function<void (T &)> start,
		std::function<void (T &, double)> update,
		std::function<void (T &, RenderCtx &)> render) 
{
	spdlog::info("Created new entity :: '{}'", id);
}

#endif
