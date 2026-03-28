#include "utils/VulkanHelpers.h"

VkDeviceQueueCreateInfo VulkanHelpers::CreateInfoHelper::SetLDQueueCretateInfo(const VulkanStructs::PDDetails& pDeviceDetails){

    float queuePriority = 0.5f;

    VkDeviceQueueCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO
    };

    info.queueFamilyIndex = pDeviceDetails.graphicsFamilyIndex;
    info.queueCount = 1;
    info.pQueuePriorities = &queuePriority;

    return info;
}

VkDeviceCreateInfo VulkanHelpers::CreateInfoHelper::SetLDCreateInfo(const VkPhysicalDeviceFeatures2& features, const std::vector<const char *>& ext,
                                                                      const VkDeviceQueueCreateInfo &queueInfo){

        VkDeviceCreateInfo info{
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO
        };

        info.pNext = &features;
        info.queueCreateInfoCount = 1;
        info.pQueueCreateInfos = &queueInfo;
        info.enabledExtensionCount = static_cast<uint32_t>(ext.size());
        info.ppEnabledExtensionNames = ext.data();

        return info;
    }
