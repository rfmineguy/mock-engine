#include "Engine/TextureAtlas.hpp"
#include "spdlog.h"

namespace Engine {
	TextureAtlas::TextureAtlas(): Texture() {
	}

	TextureAtlas::~TextureAtlas() {
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

	void TextureAtlas::Load(const std::string& filename) const {
		spdlog::info("Loading {}", filename);
	}
}
