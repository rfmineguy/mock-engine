#include "Engine/Engine.hpp"

template <typename T>
void Engine::NewEntity(const std::string& id, std::function<void (T &)> start, std::function<void (T &, double)> update, std::function<void (T &, RenderCtx &)> render) {
	
}
