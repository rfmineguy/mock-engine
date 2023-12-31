#include "Engine/Shader.hpp"
#include "Engine/Util.hpp"
#include "spdlog.h"
#include <glad/glad.h>

namespace Engine {
	Shader::Shader(const Shader::LoadData& data)
		: Resource(data.path) {
		if (!data.fragment_path.empty() && !data.vertex_path.empty()) {
			unsigned int fragmentID = InitShader(data.fragment_path, GL_FRAGMENT_SHADER);
			unsigned int vertexID = InitShader(data.vertex_path, GL_VERTEX_SHADER);
			shaderID = LinkShader(vertexID, fragmentID);
			spdlog::info("Shader loaded: {}; {}; {}", fragmentID, vertexID, shaderID);
		}
		else {
			spdlog::critical("Shader missing configuration");
		}
	}

	Shader::~Shader() {
		glDeleteProgram(shaderID);
	}

	const char* GetShaderString(GLenum type) {
		switch (type) {
			case GL_FRAGMENT_SHADER: return "Fragment";
			case GL_VERTEX_SHADER: return "Vertex";
			default: return "Unknown GLenum";
		}
	}

	unsigned int Shader::InitShader(const std::string& path, int type) {
		if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) {
			spdlog::critical("Can't create the shader with GLenum type: {} -> {}", GetShaderString((GLenum)type), type);
			return -1;
		}
		int success;
		char infoLog[512];
		
		std::string s = Engine::Util::ReadFile(path).c_str();
		const char* code = s.c_str();
		if (s.empty()) {
			spdlog::warn("Your shader ({}) is empty, this is undefined behavior", path);
		}

		// .......
		// TODO: Crash here because glad isn't setup yet...
		// .......
		unsigned int shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
			spdlog::critical("Shader Compilation Failed: {}", infoLog);
			return - 1;
		}
		spdlog::info("Shader {} compiled", path);
		return shaderID;
	}

	unsigned int Shader::LinkShader(unsigned int vertexId, unsigned int fragId) {
		unsigned int shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexId);
		glAttachShader(shaderID, fragId);
		glLinkProgram(shaderID);
		
		int success;
		char infoLog[512];
		// print linking errors if any
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
			spdlog::critical("Shader Linking Failed: {}", infoLog);
		}
			
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertexId);
		glDeleteShader(fragId);
		return shaderID;
	}

	void Shader::Bind() const {
		glUseProgram(shaderID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}

	void Shader::SetUniformX() const {
	
	}
}
