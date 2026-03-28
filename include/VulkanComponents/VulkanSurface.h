#pragma once

#include "utils/ClassUitility.h"

class VulkanInstance;
class GameWindow;

class VulkanSurface : private ClassUtilities::ImmutableOwner<VulkanSurface>{

public:
    VulkanSurface(const VulkanInstance& instance, GameWindow& window);
    ~VulkanSurface();

    bool SetupSurface();

    const VkSurfaceKHR& GetSurface() const { return mSurface; }

private:
    VkSurfaceKHR mSurface = VK_NULL_HANDLE;

    const VulkanInstance& mInstance;
    const GameWindow& mWindow;
};
