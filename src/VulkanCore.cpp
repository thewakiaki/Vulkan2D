#include "VulkanCore.h"

VulkanCore::VulkanCore(const GameWindow& window) : mGameWindow(window) {

}

VulkanCore::~VulkanCore(){

}

bool VulkanCore::InitVulkan(){

    fmt::print("Initialising Vulkan\n");

    return true;
}
