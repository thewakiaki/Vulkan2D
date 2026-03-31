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

    void RecordCommandBuffer(uint32_t imageIndex, uint32_t frameIndex);

    const VkCommandPool& GetCommandPool() const { return mCommandPool; }
    const std::array<VkCommandBuffer, MAX_FRAMES_IN_FLIGHT>& GetCommandBuffer() const { return mCommandBuffers; }

private:

    void TransitionImageLayout(uint32_t imageIndex, VulkanStructs::ImageLayout layout, uint32_t frameIndex);

    VkCommandPool mCommandPool = VK_NULL_HANDLE;

    std::array<VkCommandBuffer, MAX_FRAMES_IN_FLIGHT> mCommandBuffers;

    VulkanStructs::ImageLayout mPreRenderLayout;
    VulkanStructs::ImageLayout mPostRenderLayout;

    const VulkanPD& mPhysicalDevice;
    const VulkanLD& mLogicalDevice;
    const VulkanSC& mSwapchain;
    const VulkanGP& mGraphicsPipeline;
};
