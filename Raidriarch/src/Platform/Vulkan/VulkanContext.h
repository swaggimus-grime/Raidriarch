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
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

	private:
		VkInstance m_Instance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;

		const char** m_ExtensionNames;
		uint32_t m_ExtensionCount;

		const char* validationLayers[1] = {
			"VK_LAYER_KHRONOS_validation"
		};
	};
	
}