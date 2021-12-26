#pragma once

#include "Raid/Renderer/GraphicsContext.h"

#include "VulkanCore.h"

namespace Raid {
	class VulkanContext : public GraphicsContext {
	public:
		VulkanContext(std::vector<const char*> requiredExtensions);
		virtual ~VulkanContext() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;

		inline VkInstance& GetInstance() { return m_Instance; }
	private:
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		void VerifyValidationLayers();
		void CreateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerInfo);
	private:
		VkInstance m_Instance;

		std::vector<const char*> m_RequiredExtensions;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		const std::vector<const char*> m_ValidationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};
	};
	
}