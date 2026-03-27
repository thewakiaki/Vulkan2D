#pragma once

#include "VulkanStructs.h"

namespace VulkanHelpers {

    namespace RequirementCheck {

        bool RequiredInstanceExtensionsSupported(std::vector<const char*>& required);
        bool RequiredInstanceLayersSupported(const std::vector<const char*>& required);

        bool RequiredDeviceExtensionsSupported(const VulkanStructs::PDDetails& device, const std::vector<const char*>& required);
        bool RequiredFeaturesSupported(const VulkanStructs::PDDetails& device, const VulkanStructs::DeviceFeatures& required);
        bool GraphicsQueueSupported(const VulkanStructs::PDDetails& device);
        bool TargetAPISupported(const VulkanStructs::PDDetails& device);
    }

    namespace PDDetailExtraction{

        VkPhysicalDeviceProperties GetPDProperties(const VkPhysicalDevice& device);
        std::vector<VkExtensionProperties> GetPDExtensionProperties(const VkPhysicalDevice& device);
        std::vector<VkQueueFamilyProperties> GetPDQueueProperties(const VkPhysicalDevice& device);
        size_t GetGraphicsQueueIndex(VulkanStructs::PDDetails& deviceDetails);
        void GetSupportedFeatures(VulkanStructs::PDDetails& deviceDetails);

    }

}
