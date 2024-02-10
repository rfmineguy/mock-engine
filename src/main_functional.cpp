#include <iostream>
#include <functional>
#include "Engine/Engine.hpp"
#include "Engine/App.hpp"
#include "Engine/Entity.hpp"
#include "Engine/RenderCtx.hpp"
#include "Engine/Texture.hpp"
#include "Engine/TextureAtlas.hpp"
#include "Engine/Shader.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/Input.hpp"
#include "Engine/Vector.hpp"
#include "Engine/Scene.hpp"
#include "Test/PlayerEntity.hpp"
#include "spdlog.h"

int main() {
	Engine::App app = Engine::App(
		[&](std::shared_ptr<Engine::ResourceManager> manager) {
			manager->NewResource<Engine::Texture, Engine::Texture::LoadData>("player", [&](Engine::Texture::LoadData& data) {
				data.path = "assets/player.png";
				data.width = 32;
				data.height = 32;
			});

			std::cout << manager->Count() << std::endl;
		},
		[&](Engine::AppSettings& settings) {
			settings.windowSize = {600, 600};
			settings.clearColor = Engine::Color::FromRGB(40, 80, 70);
			// settings.enableVsync = true;
			settings.title = "Game";
		},
		[&](Engine::IEntity* const root) {
			spdlog::info("Scene setup");
			root->AddChild<PlayerEntity>("player");
			// root->GetEntityByID("player")->AddChild<PlayerEntity>("entity");
			// root->GetEntityByID("player")->AddChild<PlayerEntity>("entity2");
			// root->GetEntityByID("entity2")->AddChild<PlayerEntity>("entity3");
			// root->GetEntityByID("entity3")->AddChild<PlayerEntity>("entity4");
			root->Traverse();
		}
	);

	app.Run();
}
