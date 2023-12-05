#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "Resource.hpp"

namespace Engine {
	class Texture : public Resource {
	protected:
		std::string path;
		int width, height;

	public:
		struct LoadData : public Resource::LoadData {
			int width;
			int height;
		};
	public:
		// Texture() = delete;
		Texture(const LoadData&);
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
