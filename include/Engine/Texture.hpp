#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "Resource.hpp"

namespace Engine {
	class Texture : public Resource {
	public:
		Texture();
		~Texture();
		int GetWidth() const;
		int GetHeight() const;
		float GetAspectRatio() const;
		int GetBitDepth() const;
		int GetChannels() const;

		void Load(const std::string&) const;
	};
}

#endif
