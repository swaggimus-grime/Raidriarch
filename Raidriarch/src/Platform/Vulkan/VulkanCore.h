#pragma once

#include <vulkan/vulkan.h>
#define RAID_VK_VALIDATE(result, errMsg) RAID_CORE_ASSERT(result == VK_SUCCESS, errMsg)