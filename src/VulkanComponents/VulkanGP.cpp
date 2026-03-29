#include "VulkanComponents/VulkanGP.h"

#include "utils/VulkanHelpers.h"
#include "utils/ErrorChecking.h"

#include "VulkanComponents/VulkanSM.h"
#include "VulkanComponents/VulkanLD.h"
#include "VulkanComponents/VulkanSC.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;

VulkanGP::VulkanGP(const VulkanLD& lDevice, const VulkanSC& swapchain) : mLogicalDevice(lDevice), mSwapchain(swapchain){

}

VulkanGP::~VulkanGP(){

    for(VulkanSM& vertModule : mVertModules){
        vertModule.Cleanup();
    }

    for(VulkanSM& fragModule : mFragModules){
        fragModule.Cleanup();
    }

    if(mPipelineLayout != VK_NULL_HANDLE){
        vkDestroyPipelineLayout(mLogicalDevice.GetLogicalDevice(), mPipelineLayout, nullptr);
        mPipelineLayout = VK_NULL_HANDLE;
        fmt::print("Pipeline Layout Destroyed\n");
    }

    if(mGraphicsPipeline != VK_NULL_HANDLE){
        vkDestroyPipeline(mLogicalDevice.GetLogicalDevice(), mGraphicsPipeline, nullptr);
        mGraphicsPipeline = VK_NULL_HANDLE;
        fmt::print("Graphics Pipeline Destroyed\n");
    }
}

bool VulkanGP::SetupGraphicsPipeline(){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Graphics Pipeline\n");

    mViewport = VkViewport{0.0f, 0.0f, static_cast<float>(mSwapchain.GetSwapExtent().width), static_cast<float>(mSwapchain.GetSwapExtent().height), 0.0f, 1.0f };
    mScissor = VkRect2D{ VkOffset2D(0, 0), mSwapchain.GetSwapExtent() };

    if(!SetupShaderModules()) { return false; }

    fmt::print("----------------------------------\n");

    std::vector<VkPipelineShaderStageCreateInfo> vertShaderStageCI;
    std::vector<VkPipelineShaderStageCreateInfo> fragShaderStageCI;

    if(!SetShaderStageInfo(vertShaderStageCI, fragShaderStageCI)) { return false; }

    std::vector<VkPipelineShaderStageCreateInfo> shaderStageCI = CIHelp::CombineShaderStageInfos(vertShaderStageCI, fragShaderStageCI);
    VkPipelineDynamicStateCreateInfo dynamicStateCI = CIHelp::SetDynamicStateCI();
    VkPipelineVertexInputStateCreateInfo vertInputStateCI = CIHelp::SetVertInputStateCI();
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyCI = CIHelp::SetInputAssemblyStateCI();
    VkPipelineViewportStateCreateInfo viewportStateCI = CIHelp::SetViewportStateCI(mViewport, mScissor);
    VkPipelineRasterizationStateCreateInfo rasterStateCI = CIHelp::SetRasterStateCI();
    VkPipelineMultisampleStateCreateInfo multisampleCI = CIHelp::SetMultisampleCI();
    VkPipelineDepthStencilStateCreateInfo depthStencilCI = CIHelp::SetDepthStencilCI();
    VkPipelineColorBlendAttachmentState attatchState = CIHelp::SetColorBlendAS();
    VkPipelineColorBlendStateCreateInfo colorBlendCI = CIHelp::SetColorBlendCI(attatchState);
    VkPipelineLayoutCreateInfo pipelineLayoutCI = CIHelp::SetPipelineLayoutCI();
    VkPipelineRenderingCreateInfo renderingCI = CIHelp::SetRenderingCI(mSwapchain.GetSelectedFormat().format);

    if(!SetupPipelineLayout(pipelineLayoutCI)) { return false; }

    VkGraphicsPipelineCreateInfo graphicsPipelineCI = CIHelp::SetGraphicsPipelineCI(renderingCI, inputAssemblyCI, shaderStageCI, dynamicStateCI,
                                            vertInputStateCI, viewportStateCI, rasterStateCI, multisampleCI, depthStencilCI, colorBlendCI, mPipelineLayout);

    VkResult result = vkCreateGraphicsPipelines(mLogicalDevice.GetLogicalDevice(), VK_NULL_HANDLE, 1, &graphicsPipelineCI, nullptr, &mGraphicsPipeline);

    if(!ErrorChecking::VkResultCheck(result, "Graphics Pipeline")) { return false; }

    fmt::print("Graphics Pipeline Created\n");

    fmt::print("Graphics Pipeline Setup Complete\n");

    return true;
}

bool VulkanGP::SetupPipelineLayout(const VkPipelineLayoutCreateInfo& createInfo){

    VkResult result = vkCreatePipelineLayout(mLogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &mPipelineLayout);

    if(!ErrorChecking::VkResultCheck(result, "Pipeline Layout")) { return false; }

    fmt::print("Pipline Layout Created\n");

    return true;
}

bool VulkanGP::SetupShaderModules(){

    mVertModules.emplace_back(mLogicalDevice, ShaderType::VERTEX);
    mFragModules.emplace_back(mLogicalDevice, ShaderType::FRAGMENT);

    std::string projectRoot = PROJECT_ROOT;
    std::string compiledShaderDir = "/Assets/Compiled/Shaders/";

    std::string vertFileName = "vert.spv";
    std::string fragFileName = "frag.spv";

    std::string vertPath = projectRoot + compiledShaderDir + vertFileName;
    std::string fragPath = projectRoot + compiledShaderDir + fragFileName;

    if(!mVertModules[0].SetupShaderModule(vertPath.c_str())) { return false; }

    if(!mFragModules[0].SetupShaderModule(fragPath.c_str())) { return false; }



    return true;
}

bool VulkanGP::SetShaderStageInfo(std::vector<VkPipelineShaderStageCreateInfo>& vertInfo, std::vector<VkPipelineShaderStageCreateInfo>& fragInfo){

    if((mFragModules.size()) == 0 || (mVertModules.size() == 0)){
        fmt::print("Failed to get shader modules");
        return false;
    }

    vertInfo.resize(mVertModules.size());
    fragInfo.resize(mFragModules.size());

    for(int i = 0; i < mVertModules.size(); ++i){
        vertInfo[i]= CIHelp::SetPiplineSMCreateInfo(mVertModules[i].GetShaderModule(), mVertModules[i].GetShaderType());
    }

    for(int i = 0; i < mFragModules.size(); ++i){
        fragInfo[i]= CIHelp::SetPiplineSMCreateInfo(mFragModules[i].GetShaderModule(), mFragModules[i].GetShaderType());
    }

    return true;
}
