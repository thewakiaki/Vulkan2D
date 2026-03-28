#pragma once

#include "utils/ClassUitility.h"

namespace VulkanStructs{
    class DeviceFeatures;
}

class VulkanPD;

class VulkanLD : private ClassUtilities::ImmutableOwner<VulkanLD>{

public:
    VulkanLD(const VulkanPD& pDevice, std::vector<const char*>& requiredExt, VulkanStructs::DeviceFeatures& reqFeat);
    ~VulkanLD();

    bool SetupLogicalDevice();


    const VkDevice& GetLogicalDevice() const { return mLogicalDevice; }

private:
    void EnableDeviceFeatures(VulkanStructs::DeviceFeatures& features);

    bool SetupQueues();

    VkDevice mLogicalDevice = VK_NULL_HANDLE;

    VkQueue mGraphicsQueue = VK_NULL_HANDLE;
    VkQueue mPresentQueue = VK_NULL_HANDLE;

    const VulkanPD& mPhysicalDevice;
    const std::vector<const char*>& mRequiredDeviceExtensions;
    VulkanStructs::DeviceFeatures& mRequiredDeviceFeatures;
};
