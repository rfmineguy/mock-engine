#include "Engine/Util.hpp"
#include "spdlog.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {
	std::string Util::ReadFile(const std::string& file) {
		std::ifstream fs(file);
		if (fs.is_open()) {
			std::stringstream ss;
			ss << fs.rdbuf();
			fs.close();
			return ss.str();
		}
		spdlog::critical("Could not open file {}", file);
		return std::string("Invalid filepath");
	}

	void Util::PrintSpaces(int count) {
		for (int i = 0; i < count; i++) {
			std::cout << "   ";
		}
		std::cout << "\\_";
	}

}
