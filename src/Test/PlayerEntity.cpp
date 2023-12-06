#include "Test/PlayerEntity.hpp"
#include "Engine/RenderCtx.hpp"
#include "spdlog.h"

void PlayerEntity::Start() {
	spdlog::info("Player entity start");
}

void PlayerEntity::Update(double dt) {
	spdlog::info("Player entity update -> {}", dt);
}

void PlayerEntity::Render(Engine::RenderCtx& ctx) {
	spdlog::info("Player entity render");
}
