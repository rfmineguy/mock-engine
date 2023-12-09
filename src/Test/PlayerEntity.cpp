#include "Test/PlayerEntity.hpp"
#include "Engine/RenderCtx.hpp"
#include "Engine/ResourceManager.hpp"
#include "spdlog.h"
#include "Engine/Texture.hpp"

PlayerEntity::PlayerEntity(const std::string& id, std::shared_ptr<Engine::ResourceManager> rm): IEntity(id, rm) {}

PlayerEntity::~PlayerEntity() {}

void PlayerEntity::Start() {
	spdlog::info("Player entity start");
}

void PlayerEntity::Update(double dt) {
	spdlog::info("Player entity update -> {}", dt);
}

void PlayerEntity::Render(Engine::RenderCtx& ctx) const {
	spdlog::info("Player entity render");
	if (auto t = resourceManager->GetResource<Engine::Texture>("player")) {
		ctx.DrawRect({100, 100}, {300, 300});
		spdlog::info("PlayerEntity found player texture");
	}
}
