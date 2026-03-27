#include "VulkanCore.h"

#include "VulkanComponents/VulkanInstance.h"
#include "VulkanComponents/VulkanPD.h"

VulkanCore::VulkanCore(const GameWindow& window) : mGameWindow(window) {

    SetRequirements();

    mInstance = std::make_unique<VulkanInstance>(mVulkanRequirements.requiredInstanceExtensions, mVulkanRequirements.requiredValidationLayers);
    mPhysicalDevice = std::make_unique<VulkanPD>(*mInstance, mVulkanRequirements.requiredDeviceExtensions, mVulkanRequirements.requiredFeatures);
}

VulkanCore::~VulkanCore(){

    mPhysicalDevice.reset();
    mInstance.reset();
}

bool VulkanCore::InitVulkan(){

    if(!mInstance->SetupInstance()) { return false; }

    if(!mPhysicalDevice->SelectPhysicalDevice()) { return false; }

    fmt::print("Initialising Vulkan\n");

    return true;
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
