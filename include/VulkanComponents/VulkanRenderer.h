#pragma once

#include "utils/ClassUitility.h"
#include "utils/VulkanStructs.h"

class VulkanCmdPool;
class VulkanLD;
class VulkanSC;

class VulkanRenderer : private ClassUtilities::ImmutableOwner<VulkanRenderer>{

public:

    VulkanRenderer(VulkanCmdPool& cmdPool, const VulkanLD& lDevice, const VulkanSC& swaphchain);
    ~VulkanRenderer();

    bool SetupRenderer();
    bool DrawFrame();


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

    VulkanStructs::SyncObjects mSyncObjects;

    uint32_t mFiFIndex = 0;

    VulkanCmdPool& mCommandPool;
    const VulkanLD& mLogicalDevice;
    const VulkanSC& mSwapchain;
};
