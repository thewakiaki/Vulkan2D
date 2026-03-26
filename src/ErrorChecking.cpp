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
