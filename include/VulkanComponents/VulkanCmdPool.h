#pragma once

#include "utils/ClassUitility.h"
#include "utils/VulkanStructs.h"

class VulkanPD;
class VulkanLD;
class VulkanSC;
class VulkanGP;

class VulkanCmdPool : private ClassUtilities::ImmutableOwner<VulkanCmdPool>{

public:
    VulkanCmdPool(const VulkanPD& pDevice, const VulkanLD& lDevice, const VulkanSC& swapchain, const VulkanGP& pipeline);
    ~VulkanCmdPool();

    bool SetupCommandPool();
    bool SetupCommandBuffers();

    void RecordCommandBuffer(uint32_t imageIndex);

    const VkCommandPool& GetCommandPool() const { return mCommandPool; }
    const std::vector<VkCommandBuffer>& GetCommandBuffer() const { return mCommandBuffers; }

private:

    void TransitionImageLayout(uint32_t imageIndex, VulkanStructs::ImageLayout layout);

    VkCommandPool mCommandPool = VK_NULL_HANDLE;

    std::vector<VkCommandBuffer> mCommandBuffers;

    VulkanStructs::ImageLayout mPreRenderLayout;
    VulkanStructs::ImageLayout mPostRenderLayout;

    const VulkanPD& mPhysicalDevice;
    const VulkanLD& mLogicalDevice;
    const VulkanSC& mSwapchain;
    const VulkanGP& mGraphicsPipeline;
};
