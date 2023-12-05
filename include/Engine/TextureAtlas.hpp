#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H
#include "Resource.hpp"
#include "Texture.hpp"

namespace Engine {
	class TextureAtlas : public Texture {
	public:
		struct LoadData : public Texture::LoadData {
			int frameWidth;
			int frameHeight;
			int framesWide;
			int framesHigh;
		};
	public:
		// TextureAtlas() = delete;
		TextureAtlas(const LoadData&);
		~TextureAtlas();
		int GetFramesWide() const;
		int GetFramesTall() const;
		int GetFrameWidth() const;
		int GetFrameHeight() const;

		void Load(const std::string&) const;
	};
}

#endif
