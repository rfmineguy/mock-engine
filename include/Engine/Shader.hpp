#ifndef SHADER_H
#define SHADER_H

#include "Resource.hpp"
#include <string>
#include <unordered_map>
#include <map>
#include "glm/glm.hpp"

namespace Engine {
	class Shader : public Resource {
	private:
		unsigned int shaderID;
		std::unordered_map<std::string, unsigned int> uniformLocationMap;
		std::map<int, int> test;

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
	private:
		unsigned int GetUniformLocation(const std::string&);

	public:
		void SetUniform1f(const std::string&, float);
		void SetUniform4f(const std::string&, float, float, float, float);
		void SetUniformMat4(const std::string&, glm::mat4);

	private:
		unsigned int InitShader(const std::string&, int);
		unsigned int LinkShader(unsigned int, unsigned int);
	};
}

#endif
