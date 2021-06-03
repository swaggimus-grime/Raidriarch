#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Raid {

	class RAID_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }
	private:
		static Ref<spdlog::logger> CoreLogger;
		static Ref<spdlog::logger> ClientLogger;
	};

}

// Core log macros
#define RAID_CORE_TRACE(...)    ::Raid::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RAID_CORE_INFO(...)     ::Raid::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RAID_CORE_WARN(...)     ::Raid::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RAID_CORE_ERROR(...)    ::Raid::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RAID_CORE_FATAL(...)    ::Raid::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define RAID_TRACE(...)	      ::Raid::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RAID_INFO(...)	      ::Raid::Log::GetClientLogger()->info(__VA_ARGS__)
#define RAID_WARN(...)	      ::Raid::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RAID_ERROR(...)	      ::Raid::Log::GetClientLogger()->error(__VA_ARGS__)
#define RAID_FATAL(...)	      ::Raid::Log::GetClientLogger()->fatal(__VA_ARGS__)