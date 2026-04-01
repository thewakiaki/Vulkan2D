#pragma once

#include "utils/Constants.h"

namespace VulkanStructs{

    struct DeviceFeatures{

        VkPhysicalDeviceExtendedDynamicStateFeaturesEXT extDynState{};

        VkPhysicalDeviceVulkan13Features vulkan13Features{};

        VkPhysicalDeviceFeatures2 features2{};

        DeviceFeatures() {
            extDynState.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT;

            vulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
            vulkan13Features.pNext = &extDynState;

            features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
            features2.pNext = &vulkan13Features;
        }
    };

    struct PDDetails{
        VkPhysicalDevice pDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties properties{};
        std::vector<VkQueueFamilyProperties> queueFamilyPropeties;
        std::vector<VkExtensionProperties> extensionsProperties;

        VulkanStructs::DeviceFeatures supportedFeatures;

        int score = 0;

        bool presentInGraphicsQueue = false;

        size_t graphicsFamilyIndex = NO_FAMILY_INDEX;
        size_t presentQueueIndex = NO_FAMILY_INDEX;

        std::vector<uint32_t> queueIndices;

        PDDetails(VkPhysicalDevice device = VK_NULL_HANDLE) : pDevice(device){}
    };


    struct VulkanRequirements{
        std::vector<const char*> requiredInstanceExtensions;
        std::vector<const char*> requiredDeviceExtensions;

        std::vector<const char*> requiredValidationLayers;
        DeviceFeatures requiredFeatures;
    };

    struct ImageLayout{

        VkImageLayout oldLayout;
        VkImageLayout newLayout;
        VkAccessFlags2 srcAccessMask;
        VkAccessFlags2 dstAccessMask;
        VkPipelineStageFlags2 srcStageMask;
        VkPipelineStageFlags2 dstStageMask;
    };

    struct SyncObjects{

        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> presentCompleteSemaphores { VK_NULL_HANDLE };
        std::array<VkFence, MAX_FRAMES_IN_FLIGHT> drawFences { VK_NULL_HANDLE };

    };

    struct Vertex{
        glm::vec2 position;
        glm::vec3 color;

        static VkVertexInputBindingDescription GetBindingDescription() {

            VkVertexInputBindingDescription description{};
            description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            description.stride = sizeof(Vertex);
            description.binding = 0;
            return description;
        }

        static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescription(){
            std::array<VkVertexInputAttributeDescription, 2> description;

            description[0].binding = 0;
            description[0].location = 0;
            description[0].format = VK_FORMAT_R32G32_SFLOAT;
            description[0].offset = offsetof(Vertex, position);

            description[1].binding = 0;
            description[1].location = 1;
            description[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            description[1].offset = offsetof(Vertex, color);

            return description;
        }
    };
}
