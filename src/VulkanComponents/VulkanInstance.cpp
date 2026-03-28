#include "VulkanComponents/VulkanInstance.h"
#include "utils/ErrorChecking.h"
#include "utils/VulkanHelpers.h"
#include "utils/Constants.h"
#include "VulkanCore.h"

VulkanInstance::VulkanInstance(std::vector<const char*>& requiredExt, std::vector<const char*>& requiredLay)
                                : mRequiredExtensionNames(requiredExt), mRequiredLayerNames(requiredLay){

}

VulkanInstance::~VulkanInstance(){

    if(mInstance != VK_NULL_HANDLE){
        vkDestroyInstance(mInstance, nullptr);
        mInstance = VK_NULL_HANDLE;
        fmt::print("Instance Destroyed\n");
    }
}

bool VulkanInstance::SetupInstance(){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Instance\n");

    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo instanceInfo{};

    if(!VulkanHelpers::RequirementCheck::RequiredInstanceLayersSupported(mRequiredLayerNames)) { return false; }

    if(!VulkanHelpers::RequirementCheck::RequiredInstanceExtensionsSupported(mRequiredExtensionNames)) { return false; }

    SetAppInfo(appInfo);
    SetInstanceCI(instanceInfo, appInfo);

    VkResult result = vkCreateInstance(&instanceInfo, nullptr, &mInstance);

    if(!ErrorChecking::VkResultCheck(result, "Instance")) { return false; }

    fmt::print("Instance created\n");

    return true;
}

void VulkanInstance::SetAppInfo(VkApplicationInfo& info){
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = "Vulkan 2D";
    info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    info.pEngineName = "No Engine";
    info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    info.apiVersion = VK_API_VERSION_1_3;
}

void VulkanInstance::SetInstanceCI(VkInstanceCreateInfo& info, VkApplicationInfo& appInfo){
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &appInfo;
    info.enabledExtensionCount = mRequiredExtensionNames.size();
    info.ppEnabledExtensionNames = mRequiredExtensionNames.data();

    if(ENABLE_VALIDATION_LAYERS){
        info.enabledLayerCount = mRequiredLayerNames.size();
        info.ppEnabledLayerNames = mRequiredLayerNames.data();
    }
    else{
        info.enabledLayerCount = 0;
        info.ppEnabledLayerNames = nullptr;
    }
}
