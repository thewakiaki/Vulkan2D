#include "VulkanComponents/VulkanSC.h"

#include "utils/ErrorChecking.h"
#include "utils/VulkanHelpers.h"

#include "VulkanComponents/VulkanLD.h"
#include "VulkanComponents/VulkanPD.h"
#include "VulkanComponents/VulkanSurface.h"
#include "GameWindow.h"

namespace SCHelp = VulkanHelpers::ComponentHelper;
namespace CIHelp = VulkanHelpers::CreateInfoHelper;

VulkanSC::VulkanSC(const VulkanLD& lDevice, const VulkanPD& pDevice, const VulkanSurface& surface, GameWindow& window) :
                    mLogicalDevice(lDevice), mPhysicalDevice(pDevice), mSurface(surface), mWindow(window){

}

VulkanSC::~VulkanSC(){

    if(!mImageViews.empty()){
        for(VkImageView& imageView : mImageViews){
            vkDestroyImageView(mLogicalDevice.GetLogicalDevice(), imageView, nullptr);
            imageView = VK_NULL_HANDLE;
        }

        mImageViews.clear();
        fmt::print("Image Views Destroyed\n");
    }

    if(mSwapchain != VK_NULL_HANDLE){
        vkDestroySwapchainKHR(mLogicalDevice.GetLogicalDevice(), mSwapchain, nullptr);
        mSwapchain = VK_NULL_HANDLE;
        fmt::print("Swapchain Destroyed\n");
    }
}

bool VulkanSC::SetupSwapchain(){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Swapchain\n");

    std::vector<VkSurfaceFormatKHR> availableFormats;
    std::vector<VkPresentModeKHR> availablePresentModes;

    if(!GetSurfaceCapabilities()) { return false; }

    if(!GetSurfaceFormats(availableFormats)) { return false; }
    if(!SelectFormat(availableFormats)) { return false; }

    if(!GetSurfacePresentModes(availablePresentModes)) { return false; }
    if(!SelectPresentMode(availablePresentModes)) { return false; }

    mSwapExtent = SCHelp::SetSwapExtent(mCapabilities, mWindow.GetWindow());

    mImageCount = SelectMinImageCount();

    fmt::print("Swapchain min Image Set\n");

    VkSwapchainCreateInfoKHR createInfo = CIHelp::SetSCCreateInfo(mSurface.GetSurface(), mImageCount, mSelectedFormat, mSwapExtent,
                                                                    mSelectedPresentMode, mCapabilities, mPhysicalDevice.GetSelectedDevice());

    VkResult result = vkCreateSwapchainKHR(mLogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &mSwapchain);

    if(!ErrorChecking::VkResultCheck(result, "Swapchain")) { return false; }

    fmt::print("Swapchain Created\n");

    if(!SetupImages()) { return false; }

    fmt::print("Swapchain Setup\n");

    return true;
}

bool VulkanSC::GetSurfaceCapabilities(){


    VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mPhysicalDevice.GetSelectedDevice().pDevice, mSurface.GetSurface(), &mCapabilities);

    if(!ErrorChecking::VkResultCheck(result, "Surface Capabilities")) { return false; }

    fmt::print("Got Surface Capabilities\n");

    return true;
}

bool VulkanSC::GetSurfaceFormats(std::vector<VkSurfaceFormatKHR>& formats){

    formats.clear();

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice.GetSelectedDevice().pDevice, mSurface.GetSurface(), &formatCount, nullptr);
    formats.resize(formatCount);

    VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice.GetSelectedDevice().pDevice, mSurface.GetSurface(), &formatCount, formats.data());

    if(!ErrorChecking::VkResultCheck(result, "Surface Formats")) { return false; }

    fmt::print("Got Available Surface Formats\n");

    return true;
}

bool VulkanSC::SelectFormat(const std::vector<VkSurfaceFormatKHR>& formats){

    if(formats.empty()){
        fmt::print("No Available Formats\n");
        return false;
    }

    VkSurfaceFormatKHR targetFormat = { VK_FORMAT_B8G8R8A8_SRGB, VK_COLORSPACE_SRGB_NONLINEAR_KHR };

    for(const VkSurfaceFormatKHR& format : formats){

        if((format.format == targetFormat.format) && (format.colorSpace == targetFormat.colorSpace)){
            fmt::print("Target format avaiable, Setting Swapchain Format\n");
            mSelectedFormat = format;
            return true;
        }
    }

    mSelectedFormat = formats[0];

    fmt::print("Target Format not found using first available\n");

    return true;
}

bool VulkanSC::GetSurfacePresentModes(std::vector<VkPresentModeKHR>& modes){

    modes.clear();

    uint32_t modeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice.GetSelectedDevice().pDevice, mSurface.GetSurface(), &modeCount, nullptr);
    modes.resize(modeCount);

    VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice.GetSelectedDevice().pDevice, mSurface.GetSurface(), &modeCount, modes.data());

    if(!ErrorChecking::VkResultCheck(result, "Present Modes")) { return false; }

    fmt::print("Got Available Surface Present Modes\n");

    return true;
}


bool VulkanSC::SelectPresentMode(const std::vector<VkPresentModeKHR>& modes){

    if(modes.empty()){
        fmt::print("No available Present modes\n");
        return false;
    }

    VkPresentModeKHR targetMode = VK_PRESENT_MODE_MAILBOX_KHR;

    for(const VkPresentModeKHR& mode : modes){

        if(mode == targetMode){
            fmt::print("Target mode available, Setting Swap Surface Present Mode\n");
            mSelectedPresentMode = mode;
            return true;
        }
    }

    mSelectedPresentMode = VK_PRESENT_MODE_FIFO_KHR;
    fmt::print("Target mode not found, defaulting to FIFO mode");

    return true;
}

bool VulkanSC::SetupImages(){

    fmt::print("Setting up Swapchain Images\n");

    if(!GetSCImages()) { return false; }

    if(!SetSCImageViews()) { return false; }

    fmt::print("Swapchain Images setup\n");

    return true;
}

bool VulkanSC::GetSCImages(){

    mImages.clear();
    uint32_t imageCount;
    vkGetSwapchainImagesKHR(mLogicalDevice.GetLogicalDevice(), mSwapchain, &imageCount, nullptr);
    mImages.resize(imageCount);
    vkGetSwapchainImagesKHR(mLogicalDevice.GetLogicalDevice(), mSwapchain, &imageCount, mImages.data());

    if(mImages.empty()){
        fmt::print("Failed to get Swapchain Images\n");
        return false;
    }

    fmt::print("Retrieved Swapchain Images\n");

    return true;
}

bool VulkanSC::SetSCImageViews(){

    mImageViews.resize(mImages.size());

    for(int i = 0; i < mImages.size(); ++i){
        VkImageView imageView;

        VkImageViewCreateInfo info = CIHelp::SetIVCreateInfo(mImages[i], mSelectedFormat);
        VkResult result = vkCreateImageView(mLogicalDevice.GetLogicalDevice(), &info, nullptr, &imageView);

        if(!ErrorChecking::VkResultCheck(result, "Image View")) { return false; }

        mImageViews[i] = std::move(imageView);
    }

    fmt::print("All Image Views Created\n");

    return true;
}

uint32_t VulkanSC::SelectMinImageCount(){

    uint32_t target = mCapabilities.minImageCount + 1;

    if(mCapabilities.maxImageCount == 0){ return target; }

    if((0 < mCapabilities.maxImageCount) && (mCapabilities.maxImageCount <= mCapabilities.minImageCount)) { return mCapabilities.maxImageCount; }

    return target;
}
