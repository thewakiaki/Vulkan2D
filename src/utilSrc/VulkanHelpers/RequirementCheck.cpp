#include "utils/VulkanHelpers.h"
#include "utils/Constants.h"


bool VulkanHelpers::RequirementCheck::RequiredInstanceExtensionsSupported(std::vector<const char*>& required){

    std::vector<VkExtensionProperties> availableExt;
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    availableExt.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExt.data());

    int supportedExt = 0;

    for(uint32_t i = 0; i < required.size(); ++i){
        for(const auto& ext : availableExt){
            if(strcmp(ext.extensionName, required[i]) == 0){
                supportedExt++;
                fmt::print("Extension supported: {}\n", ext.extensionName);
                break;
            }
        }
    }

    if(required.size() != supportedExt){
        fmt::print("Not all extensions supported\n");
        return false;
    }

    fmt::print("All Required Extensions Supported\n");
    return true;
}

bool VulkanHelpers::RequirementCheck::RequiredInstanceLayersSupported(const std::vector<const char*>& required){

    if(!ENABLE_VALIDATION_LAYERS) { return true; }

    std::vector<VkLayerProperties> availableLayers;
    uint32_t availableLayerCount;
    vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);
    availableLayers.resize(availableLayerCount);
    vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers.data());

    size_t requiredCount = required.size();

    int supportedLayers = 0;

    for(size_t i = 0; i < requiredCount; ++i){
        for(const auto& layer : availableLayers){
            if(strcmp(layer.layerName, required[i]) == 0){
                supportedLayers++;
                fmt::print("Layer supported: {}\n", layer.layerName);
                break;
            }
        }
    }

    if(supportedLayers != requiredCount){
        fmt::print("Not all layers supported\n");
        return false;
    }

    fmt::print("All Required Layers Supported\n");

    return true;
}

bool VulkanHelpers::RequirementCheck::RequiredDeviceExtensionsSupported(const VulkanStructs::PDDetails &device, const std::vector<const char*>& required){

    int requiredCount = 0;

    for(size_t i = 0; i < required.size(); ++i){
        for(const VkExtensionProperties& ext : device.extensionsProperties){
            if(strcmp(ext.extensionName, required[i]) == 0){
                requiredCount++;
                fmt::print("Device Extension Supported:  {}\n", ext.extensionName);
                break;
            }
        }
    }

    if(requiredCount != required.size()){
        fmt::print("Not All Required Device Extensions Supported\n");
        return false;
    }

     fmt::print("All Required Device Extensions Supported\n");

    return true;
}

bool VulkanHelpers::RequirementCheck::RequiredFeaturesSupported(const VulkanStructs::PDDetails &device, const VulkanStructs::DeviceFeatures& required){

    if(required.vulkan13Features.dynamicRendering && !device.supportedFeatures.vulkan13Features.dynamicRendering){
        fmt::print("Feature Not Supported: Dynamic Rendering\n");
        return false;
    }

    fmt::print("Feature Supported: Dynamic Rendering\n");

    if(required.extDynState.extendedDynamicState && !device.supportedFeatures.extDynState.extendedDynamicState){
        fmt::print("Feature Not Supported: Extened Dynamic State \n");
        return false;
    }

    fmt::print("Feature Supported: Extened Dynamic State\n");

    fmt::print("All Required Features Supported\n");

    return true;
}

bool VulkanHelpers::RequirementCheck::GraphicsQueueSupported(const VulkanStructs::PDDetails& device){

    bool graphicsSupported = false;

    for(const VkQueueFamilyProperties& property : device.queueFamilyPropeties){
        if(property.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            fmt::print("Graphics Queue Supported\n");
            graphicsSupported = true;
            break;
        }
    }

    if(!graphicsSupported) { fmt::print("Graphics Queue Not Supported\n"); }

    return graphicsSupported;
}

bool VulkanHelpers::RequirementCheck::TargetAPISupported(const VulkanStructs::PDDetails &device){

    if(device.properties.apiVersion < API_VERSIONS[3].first){
        fmt::print("Target API Version {} not supported\n", API_VERSIONS[3].second);
    }

    fmt::print("Target API Version {} supported\n", API_VERSIONS[3].second);

    return true;
}
