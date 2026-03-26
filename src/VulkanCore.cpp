#include "VulkanCore.h"

#include "VulkanComponents/VulkanInstance.h"

VulkanCore::VulkanCore(const GameWindow& window) : mGameWindow(window) {

    mInstance = std::make_unique<VulkanInstance>();

}

VulkanCore::~VulkanCore(){

    mInstance.reset();

}

bool VulkanCore::InitVulkan(){

    if(!mInstance->SetupInstance()) { return false; }

    fmt::print("Initialising Vulkan\n");

    return true;
}
