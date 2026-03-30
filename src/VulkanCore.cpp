#include "VulkanCore.h"

#include "VulkanComponents/VulkanInstance.h"
#include "VulkanComponents/VulkanSurface.h"
#include "VulkanComponents/VulkanPD.h"
#include "VulkanComponents/VulkanLD.h"
#include "VulkanComponents/VulkanSC.h"
#include "VulkanComponents/VulkanGP.h"
#include "VulkanComponents/VulkanCmdPool.h"
#include "VulkanComponents/VulkanRenderer.h"

VulkanCore::VulkanCore(GameWindow& window) : mGameWindow(window) {

    SetRequirements();

    mInstance = std::make_unique<VulkanInstance>(mVulkanRequirements.requiredInstanceExtensions, mVulkanRequirements.requiredValidationLayers);
    mSurface = std::make_unique<VulkanSurface>(*mInstance, mGameWindow);
    mPhysicalDevice = std::make_unique<VulkanPD>(*mInstance, mVulkanRequirements.requiredDeviceExtensions, mVulkanRequirements.requiredFeatures, *mSurface);
    mLogicalDevice = std::make_unique<VulkanLD>(*mPhysicalDevice, mVulkanRequirements.requiredDeviceExtensions, mVulkanRequirements.requiredFeatures);
    mSwapchain = std::make_unique<VulkanSC>(*mLogicalDevice, *mPhysicalDevice, *mSurface, mGameWindow);
    mGraphicsPipeline = std::make_unique<VulkanGP>(*mLogicalDevice, *mSwapchain);
    mCommandPool = std::make_unique<VulkanCmdPool>(*mPhysicalDevice, *mLogicalDevice, *mSwapchain, *mGraphicsPipeline);
    mRenderer = std::make_unique<VulkanRenderer>(*mCommandPool, *mLogicalDevice, *mSwapchain);
}

VulkanCore::~VulkanCore(){

    mRenderer.reset();
    mCommandPool.reset();
    mGraphicsPipeline.reset();
    mSwapchain.reset();
    mLogicalDevice.reset();
    mPhysicalDevice.reset();
    mSurface.reset();
    mInstance.reset();
}

bool VulkanCore::InitVulkan(){

    fmt::print("Initialising Vulkan\n");

    if(!mInstance->SetupInstance()) { return false; }

    if(!mSurface->SetupSurface()) { return false; }

    if(!mPhysicalDevice->SelectPhysicalDevice()) { return false; }

    if(!mLogicalDevice->SetupLogicalDevice()) { return false; }

    if(!mSwapchain->SetupSwapchain()) { return false; }

    if(!mGraphicsPipeline->SetupGraphicsPipeline()) { return false; }

    if(!mCommandPool->SetupCommandPool()) { return false; }

    if(!mCommandPool->SetupCommandBuffers()) { return false; }

    if(!mRenderer->SetupRenderer()) { return false; }

    return true;
}

bool VulkanCore::DrawFrame(){

    return mRenderer->DrawFrame();
}

void VulkanCore::SetRequirements(){
    //Set Required layers and extensions here / 必須のレイヤーや拡張をここで設定してください
    mVulkanRequirements.requiredInstanceExtensions = {
        "VK_EXT_debug_utils"
    };

    AddGlfwExtensions(mVulkanRequirements.requiredInstanceExtensions);

    mVulkanRequirements.requiredValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    mVulkanRequirements.requiredDeviceExtensions = {
        "VK_KHR_swapchain"
    };

    mVulkanRequirements.requiredFeatures.vulkan13Features.pNext = &mVulkanRequirements.requiredFeatures.extDynState;
    mVulkanRequirements.requiredFeatures.features2.pNext = &mVulkanRequirements.requiredFeatures.vulkan13Features;

    mVulkanRequirements.requiredFeatures.vulkan13Features.dynamicRendering = VK_TRUE;
    mVulkanRequirements.requiredFeatures.extDynState.extendedDynamicState = VK_TRUE;
}

void VulkanCore::AddGlfwExtensions(std::vector<const char*>& required){

    uint glfwExtensionCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for(uint i = 0; i < glfwExtensionCount; ++i)
    {
        required.emplace_back(glfwExtensions[i]);
    }
}
