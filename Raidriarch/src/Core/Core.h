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