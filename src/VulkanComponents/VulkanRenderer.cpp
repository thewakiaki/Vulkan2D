#include "VulkanComponents/VulkanRenderer.h"

#include "utils/VulkanHelpers.h"
#include "utils/ErrorChecking.h"
#include "utils/Constants.h"

#include "VulkanComponents/VulkanCmdPool.h"
#include "VulkanComponents/VulkanLD.h"
#include "VulkanComponents/VulkanSC.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;

VulkanRenderer::VulkanRenderer(VulkanCmdPool& cmdPool, const VulkanLD& lDevice, VulkanSC& swaphchain)
                                : mCommandPool(cmdPool), mLogicalDevice(lDevice), mSwapchain(swaphchain) {

}

VulkanRenderer::~VulkanRenderer(){

    if(!mSyncObjects.presentCompleteSemaphores.empty()){

        for(VkSemaphore& sem : mSyncObjects.presentCompleteSemaphores){
            vkDestroySemaphore(mLogicalDevice.GetLogicalDevice(), sem, nullptr);
            sem = VK_NULL_HANDLE;
        }

        fmt::print("Present Semaphores Destroyed\n");
    }

    for(VkSemaphore& sem : mSyncObjects.renderFinishedSemaphores){
        vkDestroySemaphore(mLogicalDevice.GetLogicalDevice(), sem, nullptr);
        sem = VK_NULL_HANDLE;
    }

    fmt::print("Finished Semaphores Destroyed\n");

    for(VkFence& fence : mSyncObjects.drawFences){
        vkDestroyFence(mLogicalDevice.GetLogicalDevice(), fence, nullptr);
        fence = VK_NULL_HANDLE;
    }

    fmt::print("Draw Fences Destroyed\n");
}

bool VulkanRenderer::SetupRenderer(){
    fmt::print("----------------------------------\n");
    fmt::print("Setting Up Renderer\n");

    if(!SetupSyncObjects()) { return false; }

    fmt::print("Renderer created\n");

    return true;
}

bool VulkanRenderer::DrawFrame(){

    uint32_t imageIndex;

    if(!WaitForFences(mFiFIndex)) { return false; }

    if(!AcquireNextImage(imageIndex, mFiFIndex)) { return false; }

    if(!ResetFences(mFiFIndex)) { return false; }

    vkResetCommandBuffer(mCommandPool.GetCommandBuffer()[mFiFIndex], 0);

    mCommandPool.RecordCommandBuffer(imageIndex, mFiFIndex);

    if(!SubmitQueue(mFiFIndex, imageIndex)) { return false; }

    if(!PresentQueue(imageIndex)) { return false; }

    mFiFIndex = (mFiFIndex + 1) % MAX_FRAMES_IN_FLIGHT;

    return true;
}

bool VulkanRenderer::SetupSyncObjects(){

    fmt::print("Setting up sync objects\n");

    if(!SetupPresentSemaphores()) { return false; }

    if(!SetupFinishedSemaphores()) { return false; }

    if(!SetupFences()) { return false; }

    fmt::print("Sync objects setup\n");

    return true;
}

bool VulkanRenderer::SetupPresentSemaphores(){

    for(VkSemaphore& sem : mSyncObjects.presentCompleteSemaphores){

        VkSemaphoreCreateInfo createInfo = CIHelp::SetSemaphoreInfo();
        VkResult result = vkCreateSemaphore(mLogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &sem);

        if(!ErrorChecking::VkResultCheck(result, "Present Semaphore")) { return false; }
    }

    fmt::print("Present Semaphores Setup: {} Semaphores\n", mSyncObjects.presentCompleteSemaphores.size());

    return true;
}

bool VulkanRenderer::SetupFinishedSemaphores(){

    mSyncObjects.renderFinishedSemaphores.resize(mSwapchain.GetImages().size());

    for(VkSemaphore& sem : mSyncObjects.renderFinishedSemaphores){

        VkSemaphoreCreateInfo createInfo = CIHelp::SetSemaphoreInfo();
        VkResult result = vkCreateSemaphore(mLogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &sem);

        if(!ErrorChecking::VkResultCheck(result, "Finished Semaphore")) { return false; }
    }

    fmt::print("Finished Semaphores Setup: {} Semaphores\n", mSyncObjects.renderFinishedSemaphores.size());

    return true;
}

bool VulkanRenderer::SetupFences(){

    for(int i = 0; i < mSyncObjects.drawFences.size(); ++i){

        VkFenceCreateInfo createInfo = CIHelp::SetFenceInfo(i);

        VkResult result = vkCreateFence(mLogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &mSyncObjects.drawFences[i]);

        if(!ErrorChecking::VkResultCheck(result , "Draw Fence")) { return false; }
    }

    fmt::print("Draw Fences Created: {} Fences\n", mSyncObjects.drawFences.size());

    return true;
}

bool VulkanRenderer::WaitForFences(const uint32_t& frame){

    VkResult fenceResult = vkWaitForFences(mLogicalDevice.GetLogicalDevice(), 1, &mSyncObjects.drawFences[mFiFIndex], VK_TRUE, UINT64_MAX);

    if(!ErrorChecking::VkFailedToWaitForFences(fenceResult)) { return false; }

    return true;
}

bool VulkanRenderer::ResetFences(const uint32_t& frame){

    VkResult result = vkResetFences(mLogicalDevice.GetLogicalDevice(), 1, &mSyncObjects.drawFences[frame]);

    if(!ErrorChecking::VkFailedToResetFences(result)) { return false; }

    return true;
}

bool VulkanRenderer::AcquireNextImage(uint32_t& imageIndex, const uint32_t& frame){

    VkResult result = vkAcquireNextImageKHR(mLogicalDevice.GetLogicalDevice(), mSwapchain.GetSwapchain(), UINT64_MAX, mSyncObjects.presentCompleteSemaphores[frame],
                                                VK_NULL_HANDLE, &imageIndex);

    if(!SwapchainOK(result)) { return false; }

    return true;
}

bool VulkanRenderer::SubmitQueue(const uint32_t& frame, const uint32_t& imageIndex){

    VkPipelineStageFlags dstMask = CIHelp::SetWaitDstStageMask();
    VkSubmitInfo submitInfo = CIHelp::SetSubmitInfo(dstMask, mSyncObjects, mCommandPool.GetCommandBuffer(), frame, imageIndex);

    VkResult result = vkQueueSubmit(mLogicalDevice.GetGraphicsQueue(), 1, &submitInfo, mSyncObjects.drawFences[frame]);

    if(!ErrorChecking::VkFailedToSubmitQueue(result)) { return false; }

    return true;
}

bool VulkanRenderer::PresentQueue(const uint32_t& imageIndex){

    VkPresentInfoKHR presentInfo = CIHelp::SetPresentInfo(mSwapchain.GetSwapchain(), mSyncObjects, imageIndex);

    VkResult result = vkQueuePresentKHR(mLogicalDevice.GetPresentQueue(), &presentInfo);

    if(!SwapchainOK(result)) { return false; }

    return true;
}

bool VulkanRenderer::SwapchainOK(VkResult& result){

    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || mFramebufferResized){
        mSkipFrame = true;
        mFramebufferResized = false;
        mSwapchain.RecreateSwapchain();
        return false;
    }

    if(result != VK_SUCCESS){
        fmt::print("Fatal Error closing app {}", string_VkResult(result));
        mFatalError = true;
        return false;
    }


    return true;
}
