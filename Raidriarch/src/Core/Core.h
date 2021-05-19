#pragma once

#ifdef RAID_PLATFORM_WINDOWS
	#if RAID_DYNAMIC_LINK
		#ifdef RAID_BUILD_DLL
			#define RAID_API __declspec(dllexport)
		#else
			#define RAID_API __declspec(dllimport)
		#endif
	#else
		#define RAID_API
	#endif
#else
	#error Raidriarch only supports Windows!
#endif

#ifdef RAID_DEBUG
	#define RAID_ENABLE_ASSERTS
#endif

#ifdef RAID_ENABLE_ASSERTS
	#define RAID_ASSERT(x, ...) { if(!(x)) { RAID_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RAID_CORE_ASSERT(x, ...) { if(!(x)) { RAID_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RAID_ASSERT(x, ...)
	#define RAID_CORE_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)