#pragma once
#include "utils/ClassUitility.h"

class GameWindow;

class VulkanCore : private ClassUtilities::ImmutableOwner<VulkanCore>{

public:
    VulkanCore(const GameWindow& window);
    ~VulkanCore();

    bool InitVulkan();

private:

    const GameWindow& mGameWindow;
};
