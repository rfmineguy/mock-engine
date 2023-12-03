#include <iostream>
#include <functional>
#include "Engine/Engine.hpp"
#include "Engine/App.hpp"
#include "Engine/Texture.hpp"
#include "Engine/TextureAtlas.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/Input.hpp"
#include "Engine/Vector.hpp"

struct PlayerData {
	int x, y;
};

int main() {
	Engine::AddResource<Engine::Texture>("player", "player.png");
	Engine::AddResource<Engine::TextureAtlas>("animation", "animation.png");

	Engine::NewEntity<PlayerData>("player",
		[&](PlayerData& data) {
			// start
		},
		[&](PlayerData& data, double dt) {
			if (Engine::Input::IsKeyDown('a')) data.x --;
			if (Engine::Input::IsKeyDown('d')) data.x ++;
			if (Engine::Input::IsKeyDown('w')) data.y --;
			if (Engine::Input::IsKeyDown('s')) data.y ++;
		},
		[&](PlayerData& data, Engine::RenderCtx& ctx) {
			ctx.DrawRect({0, 0}, {0, 0});
			ctx.DrawEllipse({0, 0}, 10, 20);
			ctx.DrawTexturedRect({0, 0}, {10, 10}, Engine::GetResource<Engine::Texture>("player"));
		}
	);
	Engine::RunApp(
		[&](Engine::AppSettings settings) {
			settings.targetFPS = 30;
			settings.resizable = true;
			settings.windowSize = Engine::Vector2(600, 600);
			settings.clearColor = Engine::Color::FromRGB(100, 100, 100);
			return settings;
		}
	);
}
