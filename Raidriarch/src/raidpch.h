#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>

#include "Raid/Core/Log.h"

#include "Raid/Debug/Instrumentor.h"

#if RAID_PLATFORM_WINDOWS
	#include <Windows.h>
#endif