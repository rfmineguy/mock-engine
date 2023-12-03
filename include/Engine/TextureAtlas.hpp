#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H
#include "Resource.hpp"
#include "Texture.hpp"

namespace Engine {
	class TextureAtlas : public Texture {
	public:
		TextureAtlas();
		~TextureAtlas();
		int GetFramesWide() const;
		int GetFramesTall() const;
		int GetFrameWidth() const;
		int GetFrameHeight() const;

		void Load(const std::string&) const;
	};
}

#endif
