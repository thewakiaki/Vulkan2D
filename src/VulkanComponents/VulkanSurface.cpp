#include "VulkanComponents/VulkanSurface.h"

#include"utils/ErrorChecking.h"

#include "VulkanComponents/VulkanInstance.h"
#include "GameWindow.h"


VulkanSurface::VulkanSurface(const VulkanInstance& instance, GameWindow& window) : mInstance(instance), mWindow(window){

}

VulkanSurface::~VulkanSurface(){

    if(mSurface != VK_NULL_HANDLE){
        vkDestroySurfaceKHR(mInstance.GetInstance(), mSurface, nullptr);
        mSurface = VK_NULL_HANDLE;
        fmt::print("Surface Destroyed\n");
    }


}

bool VulkanSurface::SetupSurface(){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Surface\n");

    VkResult result = glfwCreateWindowSurface(mInstance.GetInstance(), mWindow.GetWindow(), nullptr, &mSurface);

    if(!ErrorChecking::VkResultCheck(result, "Surface")) { return false; }

    fmt::print("Surface Created\n");

    return true;
}
