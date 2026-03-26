#pragma once
#include "utils/ClassUitility.h"

class GameWindow;
class VulkanInstance;

class VulkanCore : private ClassUtilities::ImmutableOwner<VulkanCore>{

public:
    VulkanCore(const GameWindow& window);
    ~VulkanCore();

    bool InitVulkan();

private:

    std::unique_ptr<VulkanInstance> mInstance;

    const GameWindow& mGameWindow;
};
