#pragma once
#include "utils/ClassUitility.h"
#include "utils/VulkanStructs.h"

class VulkanInstance;

class VulkanPD : private ClassUtilities::ImmutableOwner<VulkanPD>{

public:
    VulkanPD(const VulkanInstance& instance, const std::vector<const char*>& requiredExt, const VulkanStructs::DeviceFeatures& reqFeat);
    ~VulkanPD();

    bool SelectPhysicalDevice();

private:
    void GetAvailableDevices(std::vector<VulkanStructs::PDDetails>& available);

    bool CheckDeviceSuitablility(const VulkanStructs::PDDetails& device);

    int ScoreDevice(const VulkanStructs::PDDetails& device);

    VulkanStructs::PDDetails SelectHighestScoring(const std::vector<VulkanStructs::PDDetails>& scoredDevices);

    VulkanStructs::PDDetails mSelectedDevice;

    const VulkanInstance& mInstance;
    const std::vector<const char*>& mRequiredDeviceExtensions;
    const VulkanStructs::DeviceFeatures& mRequiredDeviceFeatures;
};
