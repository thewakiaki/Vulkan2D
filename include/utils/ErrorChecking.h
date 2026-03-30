#pragma once

namespace ErrorChecking {

    bool GlfwWindowCheck(GLFWwindow* window, const char* errorContext);

    bool VkResultCheck(VkResult& result, const char* checkComponent);

    bool VkFailedToWaitForFences(VkResult& result);

    bool VkFailedToAcquireImage(VkResult& result);

    bool VkFailedToResetFences(VkResult& result);

    bool VkFailedToSubmitQueue(VkResult& result);

    bool VkFailedToPresentQueue(VkResult& result);
}
