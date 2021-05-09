#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>

#include "Core/Log.h"

#if RAID_PLATFORM_WINDOWS
	#include <Windows.h>
#endif