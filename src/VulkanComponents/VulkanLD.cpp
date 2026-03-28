#include "VulkanComponents/VulkanLD.h"

#include "utils/VulkanStructs.h"
#include "utils/VulkanEnums.h"

#include "utils/VulkanHelpers.h"
#include "utils/ErrorChecking.h"
#include "VulkanComponents/VulkanPD.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;

VulkanLD::VulkanLD(const VulkanPD& pDevice, std::vector<const char*>& requiredExt, VulkanStructs::DeviceFeatures& reqFeat)
                    : mPhysicalDevice(pDevice), mRequiredDeviceExtensions(requiredExt), mRequiredDeviceFeatures(reqFeat){

}

VulkanLD::~VulkanLD(){

    if(mLogicalDevice != VK_NULL_HANDLE){
        vkDestroyDevice(mLogicalDevice, nullptr);
        mLogicalDevice = VK_NULL_HANDLE;
    }

    fmt::print("Logical Device Destroyed\n");
}

bool VulkanLD::SetupLogicalDevice(){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Logical Device\n");

    EnableDeviceFeatures(mRequiredDeviceFeatures);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    queueCreateInfos.emplace_back(CIHelp::SetLDQueueCretateInfo(mPhysicalDevice.GetSelectedDevice(), FamilyType::GRAPHICS_FAMILY));

    if(!mPhysicalDevice.GetSelectedDevice().presentInGraphicsQueue) {

        fmt::print("Present Index not the same as Graphics. Adding Present Queue Info\n");
        queueCreateInfos.emplace_back(CIHelp::SetLDQueueCretateInfo(mPhysicalDevice.GetSelectedDevice(), FamilyType::PRESENT_FAMILY));
    }

    VkDeviceCreateInfo deviceCreateInfo = std::move(CIHelp::SetLDCreateInfo(mRequiredDeviceFeatures.features2, mRequiredDeviceExtensions, queueCreateInfos));

    VkResult result = vkCreateDevice(mPhysicalDevice.GetSelectedDevice().pDevice, &deviceCreateInfo, nullptr, &mLogicalDevice);

    if(!ErrorChecking::VkResultCheck(result, "Logical Device")) { return false; }

    fmt::print("Logical Device Created\n");

    if(!SetupQueues()) { return false; }

    fmt::print("Logical Device Setup Complete\n");

    return true;
}

void VulkanLD::EnableDeviceFeatures(VulkanStructs::DeviceFeatures& features){

    features.extDynState.extendedDynamicState = VK_TRUE;
    features.vulkan13Features.dynamicRendering = VK_TRUE;
    features.vulkan13Features.synchronization2 = VK_TRUE;
    features.features2.features.geometryShader = VK_TRUE;

    vkGetPhysicalDeviceFeatures2(mPhysicalDevice.GetSelectedDevice().pDevice, &features.features2);

    fmt::print("All Required Features Enabled\n");
}

bool VulkanLD::SetupQueues(){

    vkGetDeviceQueue(mLogicalDevice, mPhysicalDevice.GetSelectedDevice().graphicsFamilyIndex, 0, &mGraphicsQueue);

    if(mGraphicsQueue == VK_NULL_HANDLE){
        fmt::print("Failed To Get Graphics Queue\n");
        return false;
    }

    fmt::print("Got All Necessary Queues\n");


    return true;
}
