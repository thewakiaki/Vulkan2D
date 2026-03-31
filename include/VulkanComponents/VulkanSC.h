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
    bool RecreateSwapchain();

    const VkSwapchainKHR& GetSwapchain() const { return mSwapchain; }
    const VkSurfaceCapabilitiesKHR& GetCapabilities() const { return mCapabilities; }
    const VkSurfaceFormatKHR& GetSelectedFormat() const { return mSelectedFormat; }
    const VkPresentModeKHR& GetPresentMode() const { return mSelectedPresentMode; }
    const VkExtent2D& GetSwapExtent() const { return mSwapExtent; }
    const std::vector<VkImage>& GetImages() const { return mImages; }
    const std::vector<VkImageView>& GetImageViews() const { return mImageViews; }

private:
    bool GetSurfaceCapabilities();

    bool GetSurfaceFormats(std::vector<VkSurfaceFormatKHR>& formats);
    bool SelectFormat(const std::vector<VkSurfaceFormatKHR>& formats);

    bool GetSurfacePresentModes(std::vector<VkPresentModeKHR>& modes);
    bool SelectPresentMode(const std::vector<VkPresentModeKHR>& modes);

    bool SetupImages();
    bool GetSCImages();
    bool SetSCImageViews();

    void CleanupSwapchain();
    void CleanupSwapchainImageViews();
    void ResetMemberVars();

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
