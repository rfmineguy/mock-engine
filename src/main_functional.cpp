#include <iostream>
#include <functional>
#include "Engine/Engine.hpp"
#include "Engine/App.hpp"
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
	Engine::Init();
	Engine::App app = Engine::App(
		[&](Engine::ResourceManager& manager) {
			manager.NewResource<Engine::Texture, Engine::Texture::LoadData>("player", [&](Engine::Texture::LoadData& data) {
				data.path = "assets/player.png";
				data.width = 32;
				data.height = 32;
			});
			manager.NewResource<Engine::Shader, Engine::Shader::LoadData>("main_shader", [&](Engine::Shader::LoadData& data) {
				data.vertex_path = "assets/my_shader.vert.glsl";
				data.fragment_path = "assets/my_shader.frag.glsl";
			});
		},
		[&](Engine::AppSettings& settings) {
		},
		[&](Engine::Scene& scene) {
			scene.GetRoot()->AddChild<PlayerEntity>("player");
			scene.Traverse();
		}
	);

	app.Run();
}
