#include "raidpch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Raid {

	std::shared_ptr<spdlog::logger> Log::CoreLogger;
	std::shared_ptr<spdlog::logger> Log::ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		CoreLogger = spdlog::stdout_color_mt("RAIDRIARCH");
		CoreLogger->set_level(spdlog::level::trace);

		ClientLogger = spdlog::stdout_color_mt("APP");
		ClientLogger->set_level(spdlog::level::trace);
	}

}