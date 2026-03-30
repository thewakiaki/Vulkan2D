#pragma once

#include "utils/ClassUitility.h"

class VulkanSM;
class VulkanLD;
class VulkanSC;

class VulkanGP : private ClassUtilities::ImmutableOwner<VulkanGP>{

public:
    VulkanGP(const VulkanLD& lDevice, const VulkanSC& swapchain);
    ~VulkanGP();

    bool SetupGraphicsPipeline();

    const VkPipeline& GetPipeline() const { return mGraphicsPipeline; }

private:
    bool SetupPipelineLayout(const VkPipelineLayoutCreateInfo& createInfo);
    bool SetupShaderModules();
    bool SetShaderStageInfo(std::vector<VkPipelineShaderStageCreateInfo>& vertInfo, std::vector<VkPipelineShaderStageCreateInfo>& fragInfo);

    VkPipeline mGraphicsPipeline = VK_NULL_HANDLE;
    VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;

    VkViewport mViewport;
    VkRect2D mScissor;

    std::vector<VulkanSM> mVertModules;
    std::vector<VulkanSM> mFragModules;

    const VulkanLD& mLogicalDevice;
    const VulkanSC& mSwapchain;
};
