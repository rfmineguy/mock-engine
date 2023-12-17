#include "Test/PlayerEntity.hpp"
#include "Engine/RenderCtx.hpp"
#include "Engine/ResourceManager.hpp"
#include "spdlog.h"
#include "Engine/Texture.hpp"

PlayerEntity::PlayerEntity(const std::string& id): IEntity(id) {}

PlayerEntity::~PlayerEntity() {}

void PlayerEntity::Start() {
	spdlog::info("Player entity start");
}

void PlayerEntity::Update(double dt) {
	// spdlog::info("Player entity update -> {}", dt);
	// if (Engine::IsKeyPressed(Engine::Key::A)) {
	// 	position.x --;
	// }
	/*
	GetChild("hand").Enable();           for getting child of this entity
	GetParent().Delete();						     for deleting this entity's parent
	GetNodeID("booger").GetChild("");    for getting a child of an arbitrary entity
	*/
}

void PlayerEntity::Render(Engine::RenderCtx& ctx) const {
	// NOTE: for some reason resource manager doesn't work in here
	if (auto t = resourceManager->GetResource<Engine::Texture>("player")) {
		// spdlog::info("PlayerEntity found player texture");
		ctx.Rotate(rotation);
		ctx.Translate(position);
		ctx.DrawRect({0, 0}, {10, 10});
	}
}
