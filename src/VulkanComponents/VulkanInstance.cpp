#include "VulkanComponents/VulkanInstance.h"
#include "utils/ErrorChecking.h"

VulkanInstance::VulkanInstance(){
    mRequiredExtensionNames.clear();
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

    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo instanceInfo{};

    if(!SetupExtensions()) { return false; }

    SetAppInfo(appInfo);
    SetInstanceCI(instanceInfo, appInfo);

    VkResult result = vkCreateInstance(&instanceInfo, nullptr, &mInstance);

    if(!ErrorChecking::VkResultCheck(result, "Instance")) { return false; }

    fmt::print("Instance create\n");

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
}

bool VulkanInstance::SetupExtensions(){

    SetRequiredExtensions();

    uint glfwExtensionCount;
    mGlfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for(uint i = 0; i < glfwExtensionCount; ++i)
    {
        mRequiredExtensionNames.emplace_back(mGlfwExtensions[i]);
    }

    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    mExtensions.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, mExtensions.data());

    int supportedExt = 0;

    for(uint32_t i = 0; i < mRequiredExtensionNames.size(); ++i){
        for(const auto& ext : mExtensions){
            if(strcmp(ext.extensionName, mRequiredExtensionNames[i]) == 0){
                supportedExt++;
                fmt::print("Extension supported: {}\n", ext.extensionName);
                break;
            }
        }
    }

    if(mRequiredExtensionNames.size() != supportedExt){
        fmt::print("Not all glfw extensions supported\n");
        return false;
    }

    fmt::print("All Required Extensions Supported\n");

    return true;
}

void VulkanInstance::SetRequiredExtensions(){
    //Set Requried Extensions here dont include GLFW extensions // GLFW以外の必須拡張をここで設定してください
    mRequiredExtensionNames = { "VK_EXT_debug_utils" };
}
