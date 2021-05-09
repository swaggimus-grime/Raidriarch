#pragma once

#ifdef RAID_PLATFORM_WINDOWS
	#ifdef RAID_BUILD_DLL
		#define RAID_API __declspec(dllexport)
	#else
		#define RAID_API __declspec(dllimport)
	#endif
#else
	#error Raidriarch only supports Windows!
#endif

#ifdef RAID_ENABLE_ASSERTS
	#define RAID_ASSERT(x, ...) { if(!(x)) { RAID_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RAID_CORE_ASSERT(x, ...) { if(!(x)) { RAID_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RAID_ASSERT(x, ...)
	#define RAID_CORE_ASSERT(x, ...)
#endif



#define BIT(x) (1 << x)