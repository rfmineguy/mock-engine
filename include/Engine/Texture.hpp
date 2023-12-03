#ifndef TEXTURE_H
#define TEXTURE_H

namespace Engine {
	class Texture {
	public:
		int GetWidth() const;
		int GetHeight() const;
		float GetAspectRatio() const;
		int GetBitDepth() const;
		int GetChannels() const;
	};
}

#endif
