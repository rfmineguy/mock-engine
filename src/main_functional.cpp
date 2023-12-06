#include <iostream>
#include <functional>
#include "Engine/Engine.hpp"
#include "Engine/App.hpp"
#include "Engine/RenderCtx.hpp"
#include "Engine/Texture.hpp"
#include "Engine/TextureAtlas.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/Input.hpp"
#include "Engine/Vector.hpp"
#include "Test/PlayerEntity.hpp"

struct PlayerData {
	int x, y;
};

int main() {
	Engine::Init();

	Engine::NewResource<Engine::Texture, Engine::Texture::LoadData>("test", [&](Engine::Texture::LoadData& data) {
		data.path = "assets/test.png";
		data.width = 100;
		data.height = 100;
	});

	Engine::NewResource<Engine::TextureAtlas, Engine::TextureAtlas::LoadData>("player", [&](Engine::TextureAtlas::LoadData& data) {
		data.path = "assets/player.png";
		data.frameWidth = 32;
		data.frameHeight = 32;
	});

	if (auto t = Engine::GetResource<Engine::Texture>("test2")) {
		spdlog::info("'test': Texture => width={}, height={}", t->GetWidth(), t->GetHeight());
	}

	Engine::RunApp(
		[&](Engine::AppSettings settings) {
			settings.targetFPS = 30;
			settings.resizable = true;
			settings.windowSize = Engine::Vector2(600, 600);
			settings.clearColor = Engine::Color::FromRGB(100, 100, 100);
			return settings;
		},
		[&](Engine::Scene& scene) {
			scene.AddEntity<PlayerEntity>("enemy");
		}
	);
}
