#pragma once

#include "utils/ClassUitility.h"

class VulkanInstance : private ClassUtilities::ImmutableOwner<VulkanInstance>{

public:
    VulkanInstance();
    ~VulkanInstance();

    bool SetupInstance();

private:
    void SetAppInfo(VkApplicationInfo& info);
    void SetInstanceCI(VkInstanceCreateInfo& info, VkApplicationInfo& appInfo);

    bool SetupExtensions();
    void SetRequiredExtensions();

    VkInstance mInstance;

    const char** mGlfwExtensions;

    std::vector<VkExtensionProperties> mExtensions;
    std::vector<const char*> mRequiredExtensionNames;
};
