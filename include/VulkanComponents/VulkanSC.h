#pragma once

#include "utils/ClassUitility.h"

class VulkanPD;
class VulkanLD;
class VulkanSurface;
class GameWindow;

class VulkanSC : private ClassUtilities::ImmutableOwner<VulkanSC>{

public:
    VulkanSC(const VulkanLD& lDevice, const VulkanPD& pDevice, const VulkanSurface& surface, GameWindow& window);
    ~VulkanSC();

    bool SetupSwapchain();

    const VkSwapchainKHR& GetSwapchain() const { return mSwapchain; }
    const VkSurfaceCapabilitiesKHR& GetCapabilities() const { return mCapabilities; }
    const VkSurfaceFormatKHR& GetSelectedFormat() const { return mSelectedFormat; }
    const VkPresentModeKHR& GetPresentMode() const { return mSelectedPresentMode; }
    const VkExtent2D& GetSwapExtent() const { return mSwapExtent; }

private:
    bool GetSurfaceCapabilities();

    bool GetSurfaceFormats(std::vector<VkSurfaceFormatKHR>& formats);
    bool SelectFormat(const std::vector<VkSurfaceFormatKHR>& formats);

    bool GetSurfacePresentModes(std::vector<VkPresentModeKHR>& modes);
    bool SelectPresentMode(const std::vector<VkPresentModeKHR>& modes);

    bool SetupImages();
    bool GetSCImages();
    bool SetSCImageViews();

    uint32_t SelectMinImageCount();


    VkSwapchainKHR mSwapchain = VK_NULL_HANDLE;

    uint32_t mImageCount;

    std::vector<VkImage> mImages;
    std::vector<VkImageView> mImageViews;

    VkSurfaceCapabilitiesKHR mCapabilities;

    VkExtent2D mSwapExtent;

    VkSurfaceFormatKHR mSelectedFormat;
    VkPresentModeKHR mSelectedPresentMode;

    VkSharingMode mShareMode;

    const VulkanLD& mLogicalDevice;
    const VulkanPD& mPhysicalDevice;
    const VulkanSurface& mSurface;
    const GameWindow& mWindow;
};
