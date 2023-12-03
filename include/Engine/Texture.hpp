#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "Resource.hpp"

namespace Engine {
	class Texture : public Resource<Texture> {
	public:
		Texture() = default;
		int GetWidth() const;
		int GetHeight() const;
		float GetAspectRatio() const;
		int GetBitDepth() const;
		int GetChannels() const;

		Texture Load(const std::string&) const;
	};
}

#endif
