#include "raidpch.h"
#include "VulkanContext.h"

#include <GLFW/glfw3.h>

namespace Raid {
	VulkanContext::VulkanContext()
        :m_Instance(nullptr), m_DebugMessenger(), m_ExtensionNames(nullptr), m_ExtensionCount(0)
	{
	}

    VulkanContext::~VulkanContext() {
    #ifdef RAID_DEBUG
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");
        RAID_CORE_ASSERT(func, "Cannot load extension function {0}!", "vkDestroyDebugUtilsMessengerEXT");
        func(m_Instance, m_DebugMessenger, nullptr);
    #endif  

        vkDestroyInstance(m_Instance, nullptr);
    }

    std::vector<const char*> getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    #ifdef RAID_DEBUG
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    #endif

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

        VkInstanceCreateInfo instanceInfo{};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        auto extensions = getRequiredExtensions();
        instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instanceInfo.ppEnabledExtensionNames = extensions.data();

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

        instanceInfo.enabledLayerCount = static_cast<uint32_t>(1);
        instanceInfo.ppEnabledLayerNames = &validationLayers[0];

        VkDebugUtilsMessengerCreateInfoEXT debugMessengerInfo{};
        debugMessengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugMessengerInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugMessengerInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugMessengerInfo.pfnUserCallback = DebugCallback;
        instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessengerInfo;
    #else
        instanceInfo.enabledLayerCount = 0;
        instanceInfo.pNext = nullptr;
    #endif

        if (vkCreateInstance(&instanceInfo, nullptr, &m_Instance) != VK_SUCCESS)
            RAID_CORE_ERROR("Failed to create Vulkan instance!");

    #ifdef RAID_DEBUG
        auto createDebugMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");
        RAID_CORE_ASSERT(createDebugMessenger, "Failed to load Vulkan function!");
        RAID_CORE_ASSERT(createDebugMessenger(m_Instance, &debugMessengerInfo, nullptr, &m_DebugMessenger), "Failed to create debug messenger!");
    #endif
	}

	void VulkanContext::SwapBuffers()
	{

	}

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
        VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
    {
        const char* type;
        switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            type = "General";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            type = "Validation";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
            type = "Performance";
            break;
        default:
            RAID_CORE_WARN("Unknown message type!");
            break;
        }

        switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            RAID_CORE_INFO("Vulkan {0} info:\n {1}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            RAID_CORE_WARN("Vulkan {0} info:\n {1}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            RAID_CORE_ERROR("Vulkan {0} info:\n {1}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            RAID_CORE_TRACE("Vulkan {0} info:\n {1}", pCallbackData->pMessage);
            break;
        default:
            RAID_CORE_WARN("Unknown message severity!");
            break;
        }

        return VK_FALSE;
    }
}

