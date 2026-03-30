#include "utils/ErrorChecking.h"

bool ErrorChecking::GlfwWindowCheck(GLFWwindow *window, const char* errorContext){

    if(!window){
        fmt::print("Window {} Failed\n", errorContext);
        return false;
    }

    return true;
}

bool ErrorChecking::VkResultCheck(VkResult &result, const char* checkComponent){

    if(result != VK_SUCCESS){
        fmt::print("Failed to create: {} error type {}\n",checkComponent, string_VkResult(result));
        return false;
    }

    return true;
}

bool ErrorChecking::VkFailedToWaitForFences(VkResult &result){

    if(result != VK_SUCCESS){
        fmt::print("Failed To wait for Fences {}\n", string_VkResult(result));
        return false;
    }

    return true;
}

bool ErrorChecking::VkFailedToAcquireImage(VkResult &result){

    if(result != VK_SUCCESS){
        fmt::print("Failed to acquire next image: {}\n", string_VkResult(result));
        return false;
    }

    return true;
}

bool ErrorChecking::VkFailedToResetFences(VkResult &result){

    if(result != VK_SUCCESS){
        fmt::print("Failed to reset fences: {}\n", string_VkResult(result));
        return false;
    }

    return true;
}

bool ErrorChecking::VkFailedToSubmitQueue(VkResult &result){

    if(result != VK_SUCCESS){
        fmt::print("Failed to submit queue: {}\n", string_VkResult(result));
        return false;
    }

    return true;
}

bool ErrorChecking::VkFailedToPresentQueue(VkResult &result){

    if(result != VK_SUCCESS){
        fmt::print("Failed to present queue: {}\n", string_VkResult(result));
        return false;
    }

    return true;
}
