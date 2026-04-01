#pragma once

#include "utils/ClassUitility.h"
#include "utils/VulkanEnums.h"
#include "utils/VulkanStructs.h"

class VulkanLD;
class VulkanSC;
class VulkanPD;

class VulkanVBuffer : private ClassUtilities::ImmutableOwner<VulkanVBuffer>{

public:
    VulkanVBuffer(const VulkanPD& pDevice, const VulkanLD& lDevice, const VulkanSC& swapchain);
    ~VulkanVBuffer();

    bool SetupVertexBuffer(const std::vector<VulkanStructs::Vertex> &vertices);

    void MapMemory(const std::vector<VulkanStructs::Vertex>& vertices);

    const VkBuffer& GetVertexBuffer() const { return mVertexBuffer; }


private:
    bool SetDeviceMemory(const VkMemoryRequirements &requirement, const VkMemoryPropertyFlags &flags, const uint32_t &typeIndex);
    bool FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkBuffer mVertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory mVBufferMemory = VK_NULL_HANDLE;

    VkMemoryRequirements mMemRequirements;

    BufferType mType = BufferType::VERTEX;

    uint32_t mMemoryTypeIndex = std::numeric_limits<uint32_t>::max();

    const VulkanLD& mLogicalDevice;
    const VulkanSC& mSwapchain;
    const VulkanPD& mPhysicalDevice;
};
