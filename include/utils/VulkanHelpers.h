#pragma once

#include "VulkanStructs.h"
#include "VulkanEnums.h"

namespace VulkanHelpers {

    namespace RequirementCheck {

        bool RequiredInstanceExtensionsSupported(std::vector<const char*>& required);
        bool RequiredInstanceLayersSupported(const std::vector<const char*>& required);

        bool RequiredDeviceExtensionsSupported(const VulkanStructs::PDDetails& device, const std::vector<const char*>& required);
        bool RequiredFeaturesSupported(const VulkanStructs::PDDetails& device, const VulkanStructs::DeviceFeatures& required);
        bool GraphicsQueueSupported(const VulkanStructs::PDDetails& device);
        bool TargetAPISupported(const VulkanStructs::PDDetails& device);
    }

    namespace CreateInfoHelper{

        VkDeviceQueueCreateInfo SetLDQueueCretateInfo(const VulkanStructs::PDDetails& pDeviceDetails, FamilyType type);
        VkDeviceCreateInfo SetLDCreateInfo(const VkPhysicalDeviceFeatures2& features,
                                            const std::vector<const char*>& ext, const std::vector<VkDeviceQueueCreateInfo>& queueInfo);

        VkSwapchainCreateInfoKHR SetSCCreateInfo(const VkSurfaceKHR& surface, const uint32_t& minImageCount, const VkSurfaceFormatKHR& format,
                                                    const VkExtent2D& extent, const VkPresentModeKHR& presentMode,
                                                    const VkSurfaceCapabilitiesKHR& capabilities, const VulkanStructs::PDDetails& pDeviceDetails);
        VkImageViewCreateInfo SetIVCreateInfo(const VkImage& image, const VkSurfaceFormatKHR& format);

        VkShaderModuleCreateInfo SetSMCreateInfo(const std::vector<uint32_t>& fileData);

        VkPipelineShaderStageCreateInfo SetPiplineSMCreateInfo(const VkShaderModule& module, ShaderType type);
        std::vector<VkPipelineShaderStageCreateInfo> CombineShaderStageInfos(const std::vector<VkPipelineShaderStageCreateInfo>& vert,
                                                                             const std::vector<VkPipelineShaderStageCreateInfo>& frag);
        VkPipelineDynamicStateCreateInfo SetDynamicStateCI();
        VkPipelineVertexInputStateCreateInfo SetVertInputStateCI();
        VkPipelineInputAssemblyStateCreateInfo SetInputAssemblyStateCI();
        VkPipelineViewportStateCreateInfo SetViewportStateCI(const VkViewport& viewport, const VkRect2D& scissor);
        VkPipelineRasterizationStateCreateInfo SetRasterStateCI();
        VkPipelineMultisampleStateCreateInfo SetMultisampleCI();
        VkPipelineDepthStencilStateCreateInfo SetDepthStencilCI();
        VkPipelineColorBlendAttachmentState SetColorBlendAS();
        VkPipelineColorBlendStateCreateInfo SetColorBlendCI(const VkPipelineColorBlendAttachmentState& attachState);
        VkPipelineLayoutCreateInfo SetPipelineLayoutCI();
        VkPipelineRenderingCreateInfo SetRenderingCI(const VkFormat& format);

        VkGraphicsPipelineCreateInfo SetGraphicsPipelineCI(const VkPipelineRenderingCreateInfo& renderCI, const VkPipelineInputAssemblyStateCreateInfo& inputACI,
            const std::vector<VkPipelineShaderStageCreateInfo>& shaderStageCI, const VkPipelineDynamicStateCreateInfo& dynamicStateCI,
            const VkPipelineVertexInputStateCreateInfo& vertInputCI, const VkPipelineViewportStateCreateInfo& viewportCI,
            const VkPipelineRasterizationStateCreateInfo& rasterCI, const VkPipelineMultisampleStateCreateInfo& multisampleCI,
            const VkPipelineDepthStencilStateCreateInfo& depthStencilCI, const VkPipelineColorBlendStateCreateInfo& colorBlendCI, const VkPipelineLayout& layout);
    }

    namespace PDDetailExtraction{

        VkPhysicalDeviceProperties GetPDProperties(const VkPhysicalDevice& device);
        std::vector<VkExtensionProperties> GetPDExtensionProperties(const VkPhysicalDevice& device);
        std::vector<VkQueueFamilyProperties> GetPDQueueProperties(const VkPhysicalDevice& device);
        size_t GetGraphicsQueueIndex(VulkanStructs::PDDetails& deviceDetails, const VkSurfaceKHR& surface);
        size_t GetPresentQueueIndex(VulkanStructs::PDDetails& deviceDetails, const VkSurfaceKHR& surface);
        void GetSupportedFeatures(VulkanStructs::PDDetails& deviceDetails);

    }

    namespace SwapchainHelper {

        VkExtent2D SetSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
    }
}
