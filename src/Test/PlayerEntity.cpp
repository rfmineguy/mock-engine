#include "Test/PlayerEntity.hpp"
#include "Engine/RenderCtx.hpp"
#include "spdlog.h"

PlayerEntity::PlayerEntity(const std::string& id): IEntity(id) {}

PlayerEntity::~PlayerEntity() {}

void PlayerEntity::Start() {
	spdlog::info("Player entity start");
}

void PlayerEntity::Update(double dt) {
	spdlog::info("Player entity update -> {}", dt);
}

void PlayerEntity::Render(Engine::RenderCtx& ctx) const {
	spdlog::info("Player entity render");
}
