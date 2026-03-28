#include "utils/VulkanHelpers.h"

VkExtent2D VulkanHelpers::SwapchainHelper::SetSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window){

    VkExtent2D extent;

    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){ return capabilities.currentExtent;;}

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    extent.width = std::clamp<uint32_t>(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    extent.height = std::clamp<uint32_t>(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    fmt::print("Swap Extent Set\n");

    return extent;
}
