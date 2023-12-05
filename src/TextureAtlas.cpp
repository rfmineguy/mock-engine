#include "Engine/TextureAtlas.hpp"
#include "spdlog.h"
#include <iostream>

namespace Engine {
	TextureAtlas::TextureAtlas(const LoadData& loadData): Texture(loadData) {
		spdlog::info("  <TextureAtlas> path={}", loadData.path);
	}

	TextureAtlas::~TextureAtlas() {
		spdlog::info("	</TextureAtlas> path={}", path);
	}

	int TextureAtlas::GetFramesWide() const {
		return -1;
	}
	
	int TextureAtlas::GetFramesTall() const {
		return -1;
	}

	int TextureAtlas::GetFrameWidth() const {
		return -1;
	}

	int TextureAtlas::GetFrameHeight() const {
		return -1;
	}
}
