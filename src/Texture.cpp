#include "Engine/Texture.hpp"
#include "spdlog.h"

namespace Engine {
	Texture::Texture() {
	}

	Texture::~Texture() {
	}

	int Texture::GetWidth() const {
		return -1;
	}

	int Texture::GetHeight() const {
		return -1;
	}

	float Texture::GetAspectRatio() const {
		return -1;
	}

	int Texture::GetBitDepth() const {
		return -1;
	}

	int Texture::GetChannels() const {
		return -1;
	}

	void Texture::Load(const std::string& filename) const {
		spdlog::info("Loading {}", filename);
	}
}
