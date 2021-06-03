#include "raidpch.h"
#include "VulkanContext.h"

#include <GLFW/glfw3.h>

namespace Raid {
	VulkanContext::VulkanContext()
        :m_ExtensionNames(nullptr), m_ExtensionCount(0)
	{
	}

    VulkanContext::~VulkanContext() {
        vkDestroyInstance(m_Instance, nullptr);
    }

    std::vector<const char*> getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        //if (enableValidationLayers) {
        //    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        //}

        return extensions;
    }
    
	void VulkanContext::Init()
	{
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Default";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Raidriarch";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = m_ExtensionCount;
        createInfo.ppEnabledExtensionNames = m_ExtensionNames;

    #ifdef RAID_DEBUG
        uint32_t layerCount;
        std::vector<VkLayerProperties> availableLayers;
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        bool validationLayerKhronosFound = false;
        for (VkLayerProperties properties : availableLayers) {
            if (strcmp(properties.layerName, validationLayers[0]) == 0) {
                validationLayerKhronosFound = true;
                break;
            }
        }
        RAID_CORE_ASSERT(validationLayerKhronosFound, "Khronos validation layer not found!");

        createInfo.enabledLayerCount = static_cast<uint32_t>(1);
        createInfo.ppEnabledLayerNames = &validationLayers[0];
    #else
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    #endif

        if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) 
            RAID_CORE_ERROR("Failed to create Vulkan instance!");
	}

	void VulkanContext::SwapBuffers()
	{

	}
}

