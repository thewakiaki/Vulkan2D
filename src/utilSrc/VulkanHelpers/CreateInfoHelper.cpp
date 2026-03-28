#include "utils/VulkanHelpers.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;


VkDeviceQueueCreateInfo CIHelp::SetLDQueueCretateInfo(const VulkanStructs::PDDetails& pDeviceDetails, FamilyType type){

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

VkDeviceCreateInfo CIHelp::SetLDCreateInfo(const VkPhysicalDeviceFeatures2& features, const std::vector<const char *>& ext,
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

VkSwapchainCreateInfoKHR CIHelp::SetSCCreateInfo(const VkSurfaceKHR& surface, const uint32_t& minImageCount, const VkSurfaceFormatKHR& format,
                                                    const VkExtent2D& extent, const VkPresentModeKHR& presentMode,
                                                    const VkSurfaceCapabilitiesKHR& capabilities, const VulkanStructs::PDDetails& pDeviceDetails){

    VkSwapchainCreateInfoKHR info{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR
    };

    info.surface = surface;
    info.minImageCount = minImageCount;
    info.imageFormat = format.format;
    info.imageColorSpace = format.colorSpace;
    info.imageExtent = extent;
    info.imageArrayLayers = 1;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.preTransform = capabilities.currentTransform;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.presentMode = presentMode;
    info.clipped = true;

    if(pDeviceDetails.presentInGraphicsQueue){
        info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount = 0;
        info.pQueueFamilyIndices = nullptr;
    }
    else{
        info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        info.queueFamilyIndexCount = pDeviceDetails.queueIndices.size();
        info.pQueueFamilyIndices = pDeviceDetails.queueIndices.data();
    }

    return info;
}

VkImageViewCreateInfo CIHelp::SetIVCreateInfo(const VkImage &image, const VkSurfaceFormatKHR& format){

    VkImageViewCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO
    };

    info.flags = 0;
    info.image = image;
    info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    info.format = format.format;
    info.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    info.components = IDENTITY_COMPONENTS;

    return info;
}
