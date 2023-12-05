#include "Engine/Logger.hpp"
#include "spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
	static auto logger = spdlog::stdout_color_mt(MAIN_LOGGER);
	void SetupLogging() {
		spdlog::set_default_logger(logger);
		spdlog::info("Setup logger");
	}
}
