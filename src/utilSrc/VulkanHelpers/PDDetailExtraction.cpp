#include "utils/VulkanHelpers.h"

VkPhysicalDeviceProperties VulkanHelpers::PDDetailExtraction::GetPDProperties(const VkPhysicalDevice &device){
    VkPhysicalDeviceProperties props{};
    vkGetPhysicalDeviceProperties(device, &props);

    return props;
}

std::vector<VkExtensionProperties> VulkanHelpers::PDDetailExtraction::GetPDExtensionProperties(const VkPhysicalDevice &device){

    std::vector<VkExtensionProperties> extProps;
    uint32_t propCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &propCount, nullptr);
    extProps.resize(propCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &propCount, extProps.data());

    return extProps;
}

std::vector<VkQueueFamilyProperties> VulkanHelpers::PDDetailExtraction::GetPDQueueProperties(const VkPhysicalDevice &device){
    std::vector<VkQueueFamilyProperties> queueProps;
    uint32_t queuePropCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queuePropCount, nullptr);
    queueProps.resize(queuePropCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queuePropCount, queueProps.data());

    return queueProps;
}

void VulkanHelpers::PDDetailExtraction::GetSupportedFeatures(VulkanStructs::PDDetails& deviceDetails){

    vkGetPhysicalDeviceFeatures2(deviceDetails.pDevice, &deviceDetails.supportedFeatures.features2);
}

size_t VulkanHelpers::PDDetailExtraction::GetGraphicsQueueIndex(VulkanStructs::PDDetails &deviceDetails, const VkSurfaceKHR& surface){

    for(size_t i = 0; i < deviceDetails.queueFamilyPropeties.size(); ++i){
        if((deviceDetails.queueFamilyPropeties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0){

            VkBool32 presentSupport = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(deviceDetails.pDevice, i, surface, &presentSupport);

            if(presentSupport) { deviceDetails.presentInGraphicsQueue = true; }

            return i;
        }
    }

    return NO_FAMILY_INDEX;
}

size_t VulkanHelpers::PDDetailExtraction::GetPresentQueueIndex(VulkanStructs::PDDetails &deviceDetails, const VkSurfaceKHR &surface){

    if(deviceDetails.presentInGraphicsQueue) { return deviceDetails.graphicsFamilyIndex; }

    for(size_t i = 0; i < deviceDetails.queueFamilyPropeties.size(); ++i){

        if(i == deviceDetails.graphicsFamilyIndex) { continue; }

        VkBool32 presentSupport = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(deviceDetails.pDevice, i, surface, &presentSupport);

        if(presentSupport) {
            deviceDetails.queueIndices.emplace_back(deviceDetails.graphicsFamilyIndex);
            deviceDetails.queueIndices.emplace_back(i);
            return i;
        }
    }

    return NO_FAMILY_INDEX;
}
