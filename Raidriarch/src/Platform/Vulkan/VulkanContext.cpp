#include "raidpch.h"
#include "VulkanContext.h"

#include <GLFW/glfw3.h>

namespace Raid {
	VulkanContext::VulkanContext(std::vector<const char*> requiredExtensions)
        :m_Instance(nullptr), m_RequiredExtensions(requiredExtensions)
	{
	}

    VulkanContext::~VulkanContext() {
        if (m_DebugMessenger) {
            auto destroyMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");
            RAID_CORE_ASSERT(destroyMessenger, "Failed to retrieve address of vkDestroyDebugUtilsMessengerEXT!");
            destroyMessenger(m_Instance, m_DebugMessenger, nullptr);
        }

        vkDestroyInstance(m_Instance, nullptr);
    }
    
	void VulkanContext::Init()
	{
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Ray traycing demo";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "RAYDRIARCH";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo instanceInfo{};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfo;
        instanceInfo.enabledExtensionCount = m_RequiredExtensions.size();
        instanceInfo.ppEnabledExtensionNames = m_RequiredExtensions.data();

#ifdef RAID_DEBUG
        VerifyValidationLayers();
        instanceInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
        instanceInfo.ppEnabledLayerNames = m_ValidationLayers.data();

        VkDebugUtilsMessengerCreateInfoEXT debugMessengerInfo{};
        debugMessengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugMessengerInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugMessengerInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugMessengerInfo.pfnUserCallback = DebugCallback;

        instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessengerInfo;
        RAID_VK_VALIDATE(vkCreateInstance(&instanceInfo, nullptr, &m_Instance), "Failed to create instance!");

        CreateDebugMessenger(debugMessengerInfo);
#else
        RAYD_VK_VALIDATE(vkCreateInstance(&instanceInfo, nullptr, &m_Instance), "Failed to create instance!");
#endif
	}

	void VulkanContext::SwapBuffers()
	{

	}

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
        VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
    {
        char* type;
        switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            type = "General";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            type = "Validation";
            break;
            //VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
        default:
            type = "Performance";
            break;
        }

        switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            RAID_CORE_TRACE("Vulkan message type : {0}\n\t{1}", type, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            RAID_CORE_INFO("Vulkan message type : {0}\n\t{1}", type, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            RAID_CORE_WARN("Vulkan message type : {0}\n\t{1}", type, pCallbackData->pMessage);
            break;
            //VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
        default:
            RAID_CORE_ERROR("Vulkan message type : {0}\n\t{1}", type, pCallbackData->pMessage);
            break;
        }

        return VK_FALSE;
    }

    void VulkanContext::VerifyValidationLayers()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        RAID_CORE_ASSERT(layerCount, "Failed to find any validation layers!");

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        bool found = false;
        for (const char* layerName : m_ValidationLayers) {
            found = false;
            for (auto& props : availableLayers) {
                if (strcmp(layerName, props.layerName) == 0) {
                    found = true;
                    break;
                }
            }

            RAID_CORE_ASSERT(found, "Failed to find validation layer {0}!", layerName);
        }
    }

    void VulkanContext::CreateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerInfo)
    {
        auto createMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");
        RAID_CORE_ASSERT(createMessenger, "Failed to retrieve address of vkCreateDebugUtilsMessengerEXT!");
        createMessenger(m_Instance, &debugMessengerInfo, nullptr, &m_DebugMessenger);
    }
}

