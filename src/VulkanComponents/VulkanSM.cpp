#include "VulkanComponents/VulkanSM.h"

#include "utils/VulkanHelpers.h"
#include "utils/FileHandling.h"
#include "utils/ErrorChecking.h"

#include "VulkanComponents/VulkanLD.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;

VulkanSM::VulkanSM(const VulkanLD& lDevice) : mLogicalDevice(lDevice){

}

VulkanSM::~VulkanSM(){

    if (mShaderModule != VK_NULL_HANDLE) {

        vkDestroyShaderModule(mLogicalDevice.GetLogicalDevice(), mShaderModule, nullptr);
        mShaderModule = VK_NULL_HANDLE;
        fmt::print("Shader Module Destroyed\n");
    }
}

bool VulkanSM::SetupShaderModule(const char* filePath){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Shader Module\n");

    VkShaderModuleCreateInfo createInfo = CIHelp::SetSMCreateInfo(FileHandling::ParseFile(filePath));

    VkResult result = vkCreateShaderModule(mLogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &mShaderModule);

    if(!ErrorChecking::VkResultCheck(result, "Shader Module")) { return false; }

    fmt::print("Shader Module Created\n");

    return true;
}
