#pragma once
#include "utils/ClassUitility.h"
#include "utils/VulkanStructs.h"

class GameWindow;
class VulkanInstance;
class VulkanSurface;
class VulkanPD;
class VulkanLD;
class VulkanSC;
class VulkanGP;

class VulkanCore : private ClassUtilities::ImmutableOwner<VulkanCore>{

public:
    VulkanCore(GameWindow& window);
    ~VulkanCore();

    bool InitVulkan();

private:
    void SetRequirements();
    void AddGlfwExtensions(std::vector<const char*>& required);

    std::unique_ptr<VulkanInstance> mInstance;
    std::unique_ptr<VulkanSurface> mSurface;
    std::unique_ptr<VulkanPD> mPhysicalDevice;
    std::unique_ptr<VulkanLD> mLogicalDevice;
    std::unique_ptr<VulkanSC> mSwapchain;
    std::unique_ptr<VulkanGP> mGraphicsPipeline;

    VulkanStructs::VulkanRequirements mVulkanRequirements;

    GameWindow& mGameWindow;
};
