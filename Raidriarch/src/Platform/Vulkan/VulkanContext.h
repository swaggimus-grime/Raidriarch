#pragma once

#include "Raid/Renderer/GraphicsContext.h"
#include <vulkan/vulkan.h>

namespace Raid {
	class VulkanContext : public GraphicsContext {
	public:
		VulkanContext();
		virtual ~VulkanContext() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		VkInstance m_Instance;

		const char** m_ExtensionNames;
		uint32_t m_ExtensionCount;

		const char* validationLayers[1] = {
			"VK_LAYER_KHRONOS_validation"
		};
	};
}