#include "VulkanComponents/VulkanVBuffer.h"

#include "utils/VulkanHelpers.h"
#include "utils/ErrorChecking.h"

#include "VulkanComponents/VulkanLD.h"
#include "VulkanComponents/VulkanSC.h"
#include "VulkanComponents/VulkanPD.h"

namespace CIHelp = VulkanHelpers::CreateInfoHelper;

VulkanVBuffer::VulkanVBuffer(const VulkanPD& pDevice, const VulkanLD& lDevice, const VulkanSC& swapchain) :
                                mPhysicalDevice(pDevice), mLogicalDevice(lDevice), mSwapchain(swapchain){

}

VulkanVBuffer::~VulkanVBuffer(){

    if(mVBufferMemory != VK_NULL_HANDLE){
        vkFreeMemory(mLogicalDevice.GetLogicalDevice(), mVBufferMemory, nullptr);
        mVBufferMemory = VK_NULL_HANDLE;
        fmt::print("Device Memory Freed\n");
    }

    if(mVertexBuffer != VK_NULL_HANDLE){
        vkDestroyBuffer(mLogicalDevice.GetLogicalDevice(), mVertexBuffer, nullptr);
        mVertexBuffer = VK_NULL_HANDLE;
        fmt::print("Vertex Buffer Destroyed\n");
    }
}

bool VulkanVBuffer::SetupVertexBuffer(const std::vector<VulkanStructs::Vertex> &vertices){

    fmt::print("----------------------------------\n");
    fmt::print("Setting up Vertex Buffer\n");

    VkBufferCreateInfo createInfo = CIHelp::SetBufferCI(mSwapchain.GetSharingMode(), vertices, mType);

    VkResult result = vkCreateBuffer(mLogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &mVertexBuffer);

    if(!ErrorChecking::VkResultCheck(result, "Vertex Buffer")) { return false; }

    fmt::print("Vertex Buffer Created\n");
    fmt::print("Setting up Vertex Buffer Memory\n");

    VkMemoryRequirements memRequirements;
    VkMemoryPropertyFlags memProps = { VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT };
    vkGetBufferMemoryRequirements(mLogicalDevice.GetLogicalDevice(), mVertexBuffer, &memRequirements);

    if(!FindMemoryType(memRequirements.memoryTypeBits, memProps)) { return false; }

    if(!SetDeviceMemory(memRequirements, memProps, mMemoryTypeIndex)) { return false; }

    vkBindBufferMemory(mLogicalDevice.GetLogicalDevice(), mVertexBuffer, mVBufferMemory, 0);

    fmt::print("Vertex Buffer Setup\n");

    return true;
}

bool VulkanVBuffer::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){

    VkPhysicalDeviceMemoryProperties memProps;
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice.GetSelectedDevice().pDevice, &memProps);

    for(uint32_t i = 0; i < memProps.memoryTypeCount; ++i){

        if((typeFilter & (1 << i)) && (memProps.memoryTypes[i].propertyFlags & properties)){

            fmt::print("Found needed memory type\n");
            mMemoryTypeIndex = i;
            break;
        }
    }

    if(mMemoryTypeIndex == std::numeric_limits<uint32_t>::max()) {

        fmt::print("No suitable memory type found\n");
    }

    return true;
}

bool VulkanVBuffer::SetDeviceMemory(const VkMemoryRequirements &requirement, const VkMemoryPropertyFlags &flags, const uint32_t &typeIndex){

    VkMemoryAllocateInfo allocInfo = CIHelp::SetMemAllocateCI(requirement, flags, typeIndex);

    VkResult result = vkAllocateMemory(mLogicalDevice.GetLogicalDevice(), &allocInfo, nullptr, &mVBufferMemory);

    if(!ErrorChecking::VkResultCheck(result, "Vertex Buffer Memory")) { return false; }

    fmt::print("Vertex Buffer Memory Allocated\n");

    return true;
}

void VulkanVBuffer::MapMemory(const std::vector<VulkanStructs::Vertex>& vertices){

    uint32_t bufferSize = vertices.size() * sizeof(vertices[0]);

    void* data = nullptr;
    vkMapMemory(mLogicalDevice.GetLogicalDevice(), mVBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), bufferSize);
    vkUnmapMemory(mLogicalDevice.GetLogicalDevice(), mVBufferMemory);

    data = nullptr;

}
