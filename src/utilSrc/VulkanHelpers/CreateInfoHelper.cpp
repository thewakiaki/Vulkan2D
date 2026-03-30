#include "utils/VulkanHelpers.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;


VkDeviceQueueCreateInfo CIHelp::SetLDQueueCretateInfo(const VulkanStructs::PDDetails& pDeviceDetails, FamilyType type){

    float queuePriority = 0.5f;

    uint32_t familyIndex;

    type == FamilyType::GRAPHICS_FAMILY ? familyIndex = pDeviceDetails.graphicsFamilyIndex : familyIndex = pDeviceDetails.presentQueueIndex;

    VkDeviceQueueCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO
    };

    info.queueFamilyIndex = familyIndex;
    info.queueCount = 1;
    info.pQueuePriorities = &QUEUE_PRIORITY;

    return info;
}

VkDeviceCreateInfo CIHelp::SetLDCreateInfo(const VkPhysicalDeviceFeatures2& features, const std::vector<const char *>& ext,
                                                                      const std::vector<VkDeviceQueueCreateInfo>& queueInfo){



        VkDeviceCreateInfo info{
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO
        };

        info.pNext = &features;
        info.queueCreateInfoCount = static_cast<uint32_t>(queueInfo.size());
        info.pQueueCreateInfos = queueInfo.data();
        info.enabledExtensionCount = static_cast<uint32_t>(ext.size());
        info.ppEnabledExtensionNames = ext.data();

        return info;
}

VkSwapchainCreateInfoKHR CIHelp::SetSCCreateInfo(const VkSurfaceKHR& surface, const uint32_t& minImageCount, const VkSurfaceFormatKHR& format,
                                                    const VkExtent2D& extent, const VkPresentModeKHR& presentMode,
                                                    const VkSurfaceCapabilitiesKHR& capabilities, const VulkanStructs::PDDetails& pDeviceDetails){

    VkSwapchainCreateInfoKHR info{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR
    };

    info.surface = surface;
    info.minImageCount = minImageCount;
    info.imageFormat = format.format;
    info.imageColorSpace = format.colorSpace;
    info.imageExtent = extent;
    info.imageArrayLayers = 1;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.preTransform = capabilities.currentTransform;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.presentMode = presentMode;
    info.clipped = true;

    if(pDeviceDetails.presentInGraphicsQueue){
        info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount = 0;
        info.pQueueFamilyIndices = nullptr;
    }
    else{
        info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        info.queueFamilyIndexCount = pDeviceDetails.queueIndices.size();
        info.pQueueFamilyIndices = pDeviceDetails.queueIndices.data();
    }

    return info;
}

VkImageViewCreateInfo CIHelp::SetIVCreateInfo(const VkImage &image, const VkSurfaceFormatKHR& format){

    VkImageViewCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO
    };

    info.flags = 0;
    info.image = image;
    info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    info.format = format.format;
    info.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    info.components = IDENTITY_COMPONENTS;

    return info;
}

VkShaderModuleCreateInfo CIHelp::SetSMCreateInfo(const std::vector<uint32_t>& fileData){

    VkShaderModuleCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO
    };

    info.pNext = nullptr;
    info.flags = 0;
    info.codeSize = fileData.size() * sizeof(fileData[0]);
    info.pCode = fileData.data();

    return info;
}

VkPipelineShaderStageCreateInfo CIHelp::SetPiplineSMCreateInfo(const VkShaderModule &module, ShaderType type){

    VkPipelineShaderStageCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO
    };

    info.pName = "main";
    info.module = module;

    switch (type) {
        case ShaderType::VERTEX:
            info.stage = VK_SHADER_STAGE_VERTEX_BIT;
            break;
        case ShaderType::FRAGMENT:
            info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            break;
        default:
            throw std::runtime_error("Unspecified shader type\n");
    }

    return info;
}

std::vector<VkPipelineShaderStageCreateInfo> CIHelp::CombineShaderStageInfos(const std::vector<VkPipelineShaderStageCreateInfo>& vert,
                                                                     const std::vector<VkPipelineShaderStageCreateInfo>& frag){

    std::vector<VkPipelineShaderStageCreateInfo> info;
    info.reserve(vert.size() + frag.size());

    info.insert(info.begin(), vert.begin(), vert.end());
    info.insert(info.end(), frag.begin(), frag.end());


    return info;
}

VkPipelineDynamicStateCreateInfo CIHelp::SetDynamicStateCI(){

    VkPipelineDynamicStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO
    };

    info.dynamicStateCount = sizeof(DYNAMIC_STATES) / sizeof(DYNAMIC_STATES[0]);
    info.pDynamicStates = DYNAMIC_STATES;

    return info;
}

VkPipelineVertexInputStateCreateInfo CIHelp::SetVertInputStateCI(){

    VkPipelineVertexInputStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO
    };

    return info;
}

VkPipelineInputAssemblyStateCreateInfo CIHelp::SetInputAssemblyStateCI(){

    VkPipelineInputAssemblyStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO
    };

    info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    return info;
}

VkPipelineViewportStateCreateInfo CIHelp::SetViewportStateCI(const VkViewport& viewport, const VkRect2D& scissor){

    VkPipelineViewportStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO
    };

    info.viewportCount = 1;
    info.pViewports = &viewport;
    info.scissorCount = 1;
    info.pScissors = &scissor;


    return info;
}

VkPipelineRasterizationStateCreateInfo CIHelp::SetRasterStateCI(){

    VkPipelineRasterizationStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO
    };

    info.depthClampEnable = VK_FALSE;
    info.rasterizerDiscardEnable = VK_FALSE;
    info.polygonMode = VK_POLYGON_MODE_FILL;
    info.cullMode = VK_CULL_MODE_BACK_BIT;
    info.frontFace = VK_FRONT_FACE_CLOCKWISE;
    info.depthBiasEnable = VK_FALSE;
    info.lineWidth = 1.0f;

    return info;
}

VkPipelineMultisampleStateCreateInfo CIHelp::SetMultisampleCI(){

    VkPipelineMultisampleStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO
    };

    info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    info.sampleShadingEnable = VK_FALSE;

    return info;
}

VkPipelineDepthStencilStateCreateInfo CIHelp::SetDepthStencilCI(){

    VkPipelineDepthStencilStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO
    };

    return info;
}

VkPipelineColorBlendAttachmentState CIHelp::SetColorBlendAS(){

    VkPipelineColorBlendAttachmentState attachState{};

    attachState.blendEnable = VK_TRUE;
    attachState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    attachState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    attachState.colorBlendOp = VK_BLEND_OP_ADD;
    attachState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    attachState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    attachState.alphaBlendOp = VK_BLEND_OP_ADD;
    attachState.colorWriteMask = COLOR_WRITE_MASK;

    return attachState;
}

VkPipelineColorBlendStateCreateInfo CIHelp::SetColorBlendCI(const VkPipelineColorBlendAttachmentState& attachState){

    VkPipelineColorBlendStateCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO
    };

    info.logicOpEnable = VK_FALSE;
    info.logicOp = VK_LOGIC_OP_COPY;
    info.attachmentCount = 1;
    info.pAttachments = &attachState;

    return info;
}

VkPipelineLayoutCreateInfo CIHelp::SetPipelineLayoutCI(){

    VkPipelineLayoutCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO
    };

    info.pushConstantRangeCount = 0;
    info.setLayoutCount = 0;

    return info;
}

VkPipelineRenderingCreateInfo CIHelp::SetRenderingCI(const VkFormat &format){

    VkPipelineRenderingCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO
    };

    info.colorAttachmentCount = 1;
    info.pColorAttachmentFormats = &format;

    return info;
}

VkGraphicsPipelineCreateInfo CIHelp::SetGraphicsPipelineCI(const VkPipelineRenderingCreateInfo& renderCI, const VkPipelineInputAssemblyStateCreateInfo& inputACI,
    const std::vector<VkPipelineShaderStageCreateInfo>& shaderStageCI, const VkPipelineDynamicStateCreateInfo& dynamicStateCI,
    const VkPipelineVertexInputStateCreateInfo& vertInputCI, const VkPipelineViewportStateCreateInfo& viewportCI,
    const VkPipelineRasterizationStateCreateInfo& rasterCI, const VkPipelineMultisampleStateCreateInfo& multisampleCI,
    const VkPipelineDepthStencilStateCreateInfo& depthStencilCI, const VkPipelineColorBlendStateCreateInfo& colorBlendCI, const VkPipelineLayout& layout){

    VkGraphicsPipelineCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO
    };

    info.pNext = &renderCI;
    info.stageCount = static_cast<uint32_t>(shaderStageCI.size());
    info.pStages = shaderStageCI.data();
    info.pVertexInputState = &vertInputCI;
    info.pInputAssemblyState = &inputACI;
    info.pViewportState = &viewportCI;
    info.pRasterizationState = &rasterCI;
    info.pMultisampleState = &multisampleCI;
    info.pColorBlendState = &colorBlendCI;
    info.pDynamicState = &dynamicStateCI;
    info.layout = layout;
    info.pDepthStencilState = &depthStencilCI;
    info.renderPass = nullptr;
    info.basePipelineHandle = VK_NULL_HANDLE;
    info.basePipelineIndex = -1;

    return info;
}

VkCommandPoolCreateInfo CIHelp::SetCmdPoolCI(const VulkanStructs::PDDetails& pDevice){

    VkCommandPoolCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO
    };

    info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    info.queueFamilyIndex = pDevice.graphicsFamilyIndex;

    return info;
}

VkCommandBufferAllocateInfo CIHelp::SetBufferAllocInfo(const VkCommandPool &pool){

    VkCommandBufferAllocateInfo info{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO
    };

    info.commandPool = pool;
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    info.commandBufferCount = 1; //MAX_FRAMES_IN_FLIGHT;

    return info;
}

VkCommandBufferBeginInfo CIHelp::SetBeginInfo(){

    VkCommandBufferBeginInfo info{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO
    };

    return info;
}

VkImageMemoryBarrier2 CIHelp::SetBarrierInfo(const VulkanStructs::ImageLayout& layout, const VkImage& swapImage){

    VkImageMemoryBarrier2 barrier{};

    barrier.srcStageMask = layout.srcStageMask;
    barrier.srcAccessMask = layout.srcAccessMask;
    barrier.dstStageMask = layout.dstStageMask;
    barrier.dstAccessMask = layout.dstAccessMask;
    barrier.oldLayout = layout.oldLayout;
    barrier.newLayout = layout.newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = swapImage;
    barrier.subresourceRange = IMAGE_SUBRESOURCE_RANGE;

    return barrier;
}

VkDependencyInfo CIHelp::SetDependencyInfo(const VkImageMemoryBarrier2 &barrier){

    VkDependencyInfo info{
        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO
    };

    info.dependencyFlags = {};
    info.imageMemoryBarrierCount = 1;
    info.pImageMemoryBarriers = &barrier;

    return info;
}

VkRenderingAttachmentInfo CIHelp::SetRenderAttachInfo(const VkImageView &imageView){

    VkRenderingAttachmentInfo info{
        .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO
    };

    info.imageView = imageView;
    info.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    info.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    info.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    info.clearValue = CLEAR_COLOR;

    return info;
}

VkRenderingInfo CIHelp::SetRenderingInfo(const VkRenderingAttachmentInfo &attach, const VkExtent2D &swapExtent){

    VkRenderingInfo info{
        .sType = VK_STRUCTURE_TYPE_RENDERING_INFO
    };

    VkRect2D area;
    area.offset = { 0, 0 };
    area.extent = swapExtent;

    info.renderArea = area;
    info.layerCount = 1;
    info.colorAttachmentCount = 1;
    info.pColorAttachments = &attach;

    return info;
}
