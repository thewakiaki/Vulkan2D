#pragma once

#include "utils/ClassUitility.h"
#include "utils/VulkanStructs.h"

class VulkanCmdPool;
class VulkanLD;
class VulkanSC;

class VulkanRenderer : private ClassUtilities::ImmutableOwner<VulkanRenderer>{

public:

    VulkanRenderer(VulkanCmdPool& cmdPool, const VulkanLD& lDevice, VulkanSC& swaphchain);
    ~VulkanRenderer();

    bool SetupRenderer();
    bool DrawFrame();

    void ResizedFrameBuffer() { mFramebufferResized = true; }

private:
    bool SetupSyncObjects();
    bool SetupPresentSemaphores();
    bool SetupFinishedSemaphores();
    bool SetupFences();

    bool WaitForFences(const uint32_t& frame);
    bool AcquireNextImage(uint32_t& imageIndex, const uint32_t& frame);
    bool ResetFences(const uint32_t& frame);
    bool SubmitQueue(const uint32_t& frame, const uint32_t& imageIndex);
    bool PresentQueue(const uint32_t& imageIndex);

    bool RecreateSwapchain(VkResult& result);

    VulkanStructs::SyncObjects mSyncObjects;

    uint32_t mFiFIndex = 0;

    bool mSkipFrame = false;
    bool mFramebufferResized = false;

    VulkanCmdPool& mCommandPool;
    VulkanSC& mSwapchain;
    const VulkanLD& mLogicalDevice;
};
