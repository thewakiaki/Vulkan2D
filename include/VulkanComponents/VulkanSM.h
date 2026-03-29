#pragma once


#include "utils/VulkanEnums.h"

class VulkanLD;

class VulkanSM{

public:
    VulkanSM(const VulkanLD& lDevice, ShaderType type);
    ~VulkanSM();

    bool SetupShaderModule(const char* filePath);

    void Cleanup();

    const VkShaderModule& GetShaderModule() const { return mShaderModule; }
    const ShaderType& GetShaderType() const { return mType; }

private:
    VkShaderModule mShaderModule = VK_NULL_HANDLE;

    ShaderType mType;

    bool mManuallyCleaned = false;

    std::vector<uint32_t> mFileData;

    const VulkanLD& mLogicalDevice;
};
