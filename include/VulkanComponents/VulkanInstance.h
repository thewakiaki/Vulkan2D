#pragma once

#include "utils/ClassUitility.h"

class VulkanInstance : private ClassUtilities::ImmutableOwner<VulkanInstance>{

public:
    VulkanInstance(std::vector<const char*>& requiredExt, std::vector<const char*>& requiredLay);
    ~VulkanInstance();

    bool SetupInstance();

    const VkInstance& GetInstance() const { return mInstance; }

private:
    void SetAppInfo(VkApplicationInfo& info);
    void SetInstanceCI(VkInstanceCreateInfo& info, VkApplicationInfo& appInfo);

    bool SetupExtensions();
    void SetRequiredExtensions();

    VkInstance mInstance;

    std::vector<const char*>& mRequiredExtensionNames;
    const std::vector<const char*>& mRequiredLayerNames;
};
