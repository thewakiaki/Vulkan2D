#include "VulkanComponents/VulkanCmdPool.h"

#include "utils/VulkanHelpers.h"
#include "utils/ErrorChecking.h"

#include "VulkanComponents/VulkanPD.h"
#include "VulkanComponents/VulkanLD.h"
#include "VulkanComponents/VulkanSC.h"
#include "VulkanComponents/VulkanGP.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;
namespace CompHelp = VulkanHelpers::ComponentHelper;

VulkanCmdPool::VulkanCmdPool(const VulkanPD& pDevice, const VulkanLD& lDevice, const VulkanSC& swapchain, const VulkanGP& pipeline)
                                : mPhysicalDevice(pDevice), mLogicalDevice(lDevice), mSwapchain(swapchain), mGraphicsPipeline(pipeline){

    mPreRenderLayout = CompHelp::SetImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                                            {}, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
                                            VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT);

    mPostRenderLayout = CompHelp::SetImageLayout(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                                            VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT, {},
                                            VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT);
}

VulkanCmdPool::~VulkanCmdPool(){

    if(mCommandPool != VK_NULL_HANDLE){
        vkDestroyCommandPool(mLogicalDevice.GetLogicalDevice(), mCommandPool, nullptr);
        mCommandPool = VK_NULL_HANDLE;
        fmt::print("Command Pool Destroyed\n");
    }
}

bool VulkanCmdPool::SetupCommandPool(){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Command Pool\n");

    VkCommandPoolCreateInfo poolInfo = CIHelp::SetCmdPoolCI(mPhysicalDevice.GetSelectedDevice());

    VkResult result = vkCreateCommandPool(mLogicalDevice.GetLogicalDevice(), &poolInfo, nullptr, &mCommandPool);

    if(!ErrorChecking::VkResultCheck(result, "Command Pool")) { return false; }

    fmt::print("Command Pool Created\n");

    return true;
}

bool VulkanCmdPool::SetupCommandBuffers(){
    fmt::print("----------------------------------\n");
    fmt::print("Setting up Command Buffers\n");

    VkCommandBufferAllocateInfo allocInfo = CIHelp::SetBufferAllocInfo(mCommandPool);

    mCommandBuffers.resize(1);

    VkResult result = vkAllocateCommandBuffers(mLogicalDevice.GetLogicalDevice(), &allocInfo, &mCommandBuffers[0]);

    if(!ErrorChecking::VkResultCheck(result, "Command Buffer")) { return false; }

    fmt::print("Command Buffers Created\n");

    return true;
}

void VulkanCmdPool::RecordCommandBuffer(uint32_t imageIndex){

    VkCommandBufferBeginInfo beginInfo = CIHelp::SetBeginInfo();

    vkBeginCommandBuffer(mCommandBuffers[0], &beginInfo);

    TransitionImageLayout(imageIndex, mPreRenderLayout);

    VkRenderingAttachmentInfo attachInfo = CIHelp::SetRenderAttachInfo(mSwapchain.GetImageViews()[imageIndex]);
    VkRenderingInfo renderingInfo = CIHelp::SetRenderingInfo(attachInfo, mSwapchain.GetSwapExtent());

    vkCmdBeginRendering(mCommandBuffers[0], &renderingInfo);

    vkCmdBindPipeline(mCommandBuffers[0], VK_PIPELINE_BIND_POINT_GRAPHICS, mGraphicsPipeline.GetPipeline());

    VkViewport viewport = VkViewport(0.0f, 0.0f, static_cast<float>(mSwapchain.GetSwapExtent().width),
                                     static_cast<float>(mSwapchain.GetSwapExtent().height), 0.0f, 1.0f);
    VkRect2D scissor = VkRect2D(VkOffset2D(0, 0), mSwapchain.GetSwapExtent());

    vkCmdSetViewport(mCommandBuffers[0], 0, 1, &viewport);
    vkCmdSetScissor(mCommandBuffers[0], 0, 1, &scissor);

    vkCmdDraw(mCommandBuffers[0], 3, 1, 0, 0);

    vkCmdEndRendering(mCommandBuffers[0]);

    TransitionImageLayout(imageIndex, mPostRenderLayout);

    vkEndCommandBuffer(mCommandBuffers[0]);

}

void VulkanCmdPool::TransitionImageLayout(uint32_t imageIndex, VulkanStructs::ImageLayout layout){

    VkImageMemoryBarrier2 barrier = CIHelp::SetBarrierInfo(layout, mSwapchain.GetImages()[imageIndex]);

    VkDependencyInfo dependecyInfo = CIHelp::SetDependencyInfo(barrier);

    vkCmdPipelineBarrier2(mCommandBuffers[0], &dependecyInfo);

}
