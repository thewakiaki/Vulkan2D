#pragma once

#include "utils/ClassUitility.h"

class VulkanLD;

class VulkanSM : private ClassUtilities::ImmutableOwner<VulkanSM>{

public:
    VulkanSM(const VulkanLD& lDevice);
    ~VulkanSM();

    bool SetupShaderModule(const char* filePath);

private:
    VkShaderModule mShaderModule = VK_NULL_HANDLE;

    const VulkanLD& mLogicalDevice;
};
