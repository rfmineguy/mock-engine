#include "Test/PlayerEntity.hpp"
#include "Engine/Color.hpp"
#include "Engine/RenderCtx.hpp"
#include "Engine/ResourceManager.hpp"
#include "spdlog.h"
#include "Engine/Texture.hpp"

PlayerEntity::PlayerEntity(const std::string& id): IEntity(id), r(100) {}

PlayerEntity::~PlayerEntity() {}

void PlayerEntity::Start() {
	spdlog::info("Player entity start");
}

void PlayerEntity::Update(double dt) {
	time += dt;
	// r = sin(time) * 50;
	// spdlog::info("{} : {}", time, r);
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
	// ctx.Rotate(rotation);
	// ctx.Translate(position);
	ctx.DrawRect({0,0}, {10,10}, Engine::Color::Black());
	ctx.DrawCircle({0, 0}, 100, Engine::Color::FromRGB(r, 34, 31));
}
