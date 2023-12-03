#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H
#include "Texture.hpp"

namespace Engine {
	class TextureAtlas : public Texture {
		int GetFramesWide() const;
		int GetFramesTall() const;
		int GetFrameWidth() const;
		int GetFrameHeight() const;
	};
}

#endif
