#include "VulkanComponents/VulkanPD.h"
#include "VulkanComponents/VulkanInstance.h"
#include "utils/VulkanHelpers.h"

VulkanPD::VulkanPD(const VulkanInstance& instance, const std::vector<const char*>& requiredExt, const VulkanStructs::DeviceFeatures& reqFeat)
                    : mInstance(instance), mRequiredDeviceExtensions(requiredExt), mRequiredDeviceFeatures(reqFeat){
    mSelectedDevice = VulkanStructs::PDDetails();
}

VulkanPD::~VulkanPD(){

    fmt::print("Physical Device Cleaned up\n");

}

bool VulkanPD::SelectPhysicalDevice(){

    fmt::print("----------------------------------\n");
    fmt::print("Selecting Physical Device\n");

    std::vector<VulkanStructs::PDDetails> available;
    std::vector<VulkanStructs::PDDetails> compatibleDevices;

    GetAvailableDevices(available);

    if(available.empty()){
        fmt::print("No Available Devices\n");
        return false;
    }

    for(const VulkanStructs::PDDetails& device : available){
        if(!CheckDeviceSuitablility(device)) {
            fmt::print("Device Not Compatible\n");
            continue;
        }

        fmt::print("Compatible Device found: {}\n", device.properties.deviceName);
        compatibleDevices.emplace_back(device);
    }

    if(compatibleDevices.empty()){
        fmt::print("No Compatible Devices\n");
        return false;
    }

    if(compatibleDevices.size() < 2){

        mSelectedDevice = std::move(compatibleDevices[0]);
        fmt::print("Physical Device selected: {}\n", mSelectedDevice.properties.deviceName);
        return true;
    }

    for(VulkanStructs::PDDetails& device : compatibleDevices){
        device.score = ScoreDevice(device);
    }

    mSelectedDevice = std::move(SelectHighestScoring(compatibleDevices));

    fmt::print("Physical Device selected: {}\n", mSelectedDevice.properties.deviceName);

    return true;
}

void VulkanPD::GetAvailableDevices(std::vector<VulkanStructs::PDDetails>& available){
    std::vector<VkPhysicalDevice> devices;
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(mInstance.GetInstance(), &deviceCount, nullptr);
    devices.resize(deviceCount);
    vkEnumeratePhysicalDevices(mInstance.GetInstance(), &deviceCount, devices.data());

    for(const VkPhysicalDevice& device : devices){
        VulkanStructs::PDDetails details = VulkanStructs::PDDetails(device);
        details.properties = VulkanHelpers::PDDetailExtraction::GetPDProperties(device);
        details.queueFamilyPropeties = VulkanHelpers::PDDetailExtraction::GetPDQueueProperties(device);
        details.graphicsFamilyIndex = VulkanHelpers::PDDetailExtraction::GetGraphicsQueueIndex(details);
        details.extensionsProperties = VulkanHelpers::PDDetailExtraction::GetPDExtensionProperties(device);
        VulkanHelpers::PDDetailExtraction::GetSupportedFeatures(details);
        available.emplace_back(details);
    }

    return;
}

bool VulkanPD::CheckDeviceSuitablility(const VulkanStructs::PDDetails& device){

    if(!VulkanHelpers::RequirementCheck::GraphicsQueueSupported(device)) { return false; }

    if(!VulkanHelpers::RequirementCheck::TargetAPISupported(device)) { return false; }

    if(!VulkanHelpers::RequirementCheck::RequiredDeviceExtensionsSupported(device, mRequiredDeviceExtensions)) { return false; }

    if(!VulkanHelpers::RequirementCheck::RequiredFeaturesSupported(device, mRequiredDeviceFeatures)) { return false; }

    return true;
}

int VulkanPD::ScoreDevice(const VulkanStructs::PDDetails& device){

    int score = 0;

    switch (device.properties.deviceType) {
           case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
               score += 2000;
               break;
           case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
               score += 1000;
               break;
           default:
               score += 0;
               break;
       }

       VkPhysicalDeviceFeatures features{};
       vkGetPhysicalDeviceFeatures(device.pDevice, &features);

       if (features.robustBufferAccess) { score+= 130; }
       if (features.wideLines) { score+= 100; }
       if (features.sampleRateShading) { score+= 70; }

       if (features.independentBlend) { score+= 60; }
       if (features.wideLines) { score+= 60; }
       if (features.depthClamp) { score+= 40; }
       if (features.fillModeNonSolid) { score+= 40; }

       if (features.occlusionQueryPrecise) { score+= 35; }
       if (features.depthBiasClamp) { score+= 33; }
       if (features.dualSrcBlend) { score+= 32; }

       fmt::print("Device: {} scored: {}\n", device.properties.deviceName, score);

       return score;
}

VulkanStructs::PDDetails VulkanPD::SelectHighestScoring(const std::vector<VulkanStructs::PDDetails>& scoredDevices){

    int highestScoring = 0;

    for(int i = 0; i < scoredDevices.size(); ++i){
        if(scoredDevices[i].score > scoredDevices[highestScoring].score){
            highestScoring = i;
        }
    }

    return scoredDevices[highestScoring];
}
