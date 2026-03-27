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
    deviceDetails.supportedFeatures.vulkan13Features.pNext = &deviceDetails.supportedFeatures.extDynState;
    deviceDetails.supportedFeatures.features2.pNext = &deviceDetails.supportedFeatures.vulkan13Features;

    vkGetPhysicalDeviceFeatures2(deviceDetails.pDevice, deviceDetails.supportedFeatures.GetFeatures());
}

size_t VulkanHelpers::PDDetailExtraction::GetGraphicsQueueIndex(VulkanStructs::PDDetails &deviceDetails){

    for(size_t i = 0; i < deviceDetails.queueFamilyPropeties.size(); ++i){
        if((deviceDetails.queueFamilyPropeties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0){
            return i;
        }
    }

    return NO_FAMILY_INDEX;
}
