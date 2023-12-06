#include "Engine/Texture.hpp"
#include "spdlog.h"
#include <iostream>

namespace Engine {
	Texture::Texture(const LoadData& loadData)
		: Resource(loadData.path), path(loadData.path), width(loadData.width), height(loadData.height) {
		spdlog::info("<Texture> path={}", loadData.path);
	}

	Texture::~Texture() {
		spdlog::info("</Texture> path={}", path);
		// no using spdlog here, for some reason it's been uninitialized
	}

	int Texture::GetWidth() const {
		return width;
	}

	int Texture::GetHeight() const {
		return height;
	}

	float Texture::GetAspectRatio() const {
		return (float) GetWidth() / GetHeight();
	}

	int Texture::GetBitDepth() const {
		return -1;
	}

	int Texture::GetChannels() const {
		return -1;
	}
}
