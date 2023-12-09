#ifndef SHADER_H
#define SHADER_H

#include "Resource.hpp"
#include <string>

namespace Engine {
	class Shader : public Resource {
	private:
		unsigned int shaderID;
	public:
		struct LoadData : public Resource::LoadData {
			std::string vertex_path, fragment_path;
		};
	public:
		Shader(const LoadData&);
		~Shader();
		int GetHandle() const;
	public:
		void Bind() const;
		void Unbind() const;
		void SetUniformX() const;

	private:
		unsigned int InitShader(const std::string&, int);
		unsigned int LinkShader(unsigned int, unsigned int);
	};
}

#endif
