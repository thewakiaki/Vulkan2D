#include "utils/VulkanHelpers.h"



VkDeviceQueueCreateInfo VulkanHelpers::CreateInfoHelper::SetLDQueueCretateInfo(const VulkanStructs::PDDetails& pDeviceDetails, FamilyType type){

    float queuePriority = 0.5f;

    uint32_t familyIndex;

    type == FamilyType::GRAPHICS_FAMILY ? familyIndex = pDeviceDetails.graphicsFamilyIndex : familyIndex = pDeviceDetails.presentQueueIndex;

    VkDeviceQueueCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO
    };

    info.queueFamilyIndex = familyIndex;
    info.queueCount = 1;
    info.pQueuePriorities = &QUEUE_PRIORITY;

    return info;
}

VkDeviceCreateInfo VulkanHelpers::CreateInfoHelper::SetLDCreateInfo(const VkPhysicalDeviceFeatures2& features, const std::vector<const char *>& ext,
                                                                      const std::vector<VkDeviceQueueCreateInfo>& queueInfo){



        VkDeviceCreateInfo info{
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO
        };

        info.pNext = &features;
        info.queueCreateInfoCount = static_cast<uint32_t>(queueInfo.size());
        info.pQueueCreateInfos = queueInfo.data();
        info.enabledExtensionCount = static_cast<uint32_t>(ext.size());
        info.ppEnabledExtensionNames = ext.data();

        return info;
    }
