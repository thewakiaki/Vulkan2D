#pragma once

#include "utils/Constants.h"

namespace VulkanStructs{

    struct DeviceFeatures{

        VkPhysicalDeviceFeatures2* GetFeatures() { return &features2; }

        VkPhysicalDeviceExtendedDynamicStateFeaturesEXT extDynState{
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT
        };

        VkPhysicalDeviceVulkan13Features vulkan13Features{
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES
        };

        VkPhysicalDeviceFeatures2 features2{
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
        };

    };

    struct PDDetails{
        VkPhysicalDevice pDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties properties{};
        std::vector<VkQueueFamilyProperties> queueFamilyPropeties;
        std::vector<VkExtensionProperties> extensionsProperties;

        VulkanStructs::DeviceFeatures supportedFeatures;

        int score = 0;

        size_t graphicsQueueIndex = NO_FAMILY_INDEX;
        size_t presentQueueIndex = NO_FAMILY_INDEX;

        PDDetails(VkPhysicalDevice device = VK_NULL_HANDLE) : pDevice(device){}
    };


    struct VulkanRequirements{
        std::vector<const char*> requiredInstanceExtensions;
        std::vector<const char*> requiredDeviceExtensions;

        std::vector<const char*> requiredValidationLayers;
        DeviceFeatures requiredFeatures;
    };

}
