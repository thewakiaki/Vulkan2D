#pragma once
#include "utils/ClassUitility.h"
#include "utils/VulkanStructs.h"

class GameWindow;
class VulkanInstance;
class VulkanPD;
class VulkanLD;

class VulkanCore : private ClassUtilities::ImmutableOwner<VulkanCore>{

public:
    VulkanCore(const GameWindow& window);
    ~VulkanCore();

    bool InitVulkan();

    VulkanStructs::VulkanRequirements& GetVulkanRequirements() { return this->mVulkanRequirements; }

private:
    void SetRequirements();
    void AddGlfwExtensions(std::vector<const char*>& required);

    std::unique_ptr<VulkanInstance> mInstance;
    std::unique_ptr<VulkanPD> mPhysicalDevice;
    std::unique_ptr<VulkanLD> mLogicalDevice;

    VulkanStructs::VulkanRequirements mVulkanRequirements;

    const GameWindow& mGameWindow;
};
