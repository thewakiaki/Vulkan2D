#pragma once

constexpr uint32_t WINDOW_WIDTH = 800;
constexpr uint32_t WINDOW_HEIGHT = 600;

constexpr bool ENABLE_VALIDATION_LAYERS = true;

constexpr size_t MAX_FRAMES_IN_FLIGHT = 2;

constexpr float QUEUE_PRIORITY = 0.5f;

constexpr const char* REQUIRED_VALIDATION_LAYERS[] = {
    "VK_LAYER_KHRONOS_validation"
};

constexpr size_t NO_FAMILY_INDEX = std::numeric_limits<size_t>::max();

constexpr VkClearValue CLEAR_COLOR{ 0.1f, 0.1f, 0.1f, 1.0f };

constexpr std::array<std::pair<uint32_t, const char*>, 5> API_VERSIONS = {{
    {VK_API_VERSION_1_0, "VULKAN API VERSION 1.0"},
    {VK_API_VERSION_1_1, "VULKAN API VERSION 1.1"},
    {VK_API_VERSION_1_2, "VULKAN API VERSION 1.2"},
    {VK_API_VERSION_1_3, "VULKAN API VERSION 1.3"},
    {VK_API_VERSION_1_4, "VULKAN API VERSION 1.4"}
}};

constexpr VkComponentMapping IDENTITY_COMPONENTS = {
    VK_COMPONENT_SWIZZLE_IDENTITY,
    VK_COMPONENT_SWIZZLE_IDENTITY,
    VK_COMPONENT_SWIZZLE_IDENTITY,
    VK_COMPONENT_SWIZZLE_IDENTITY
};

constexpr VkDynamicState DYNAMIC_STATES[] = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
};

constexpr VkColorComponentFlags COLOR_WRITE_MASK{
    VK_COLOR_COMPONENT_R_BIT |
    VK_COLOR_COMPONENT_G_BIT |
    VK_COLOR_COMPONENT_B_BIT |
    VK_COLOR_COMPONENT_A_BIT
};

constexpr VkImageSubresourceRange IMAGE_SUBRESOURCE_RANGE{
    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
    .baseMipLevel = 0,
    .levelCount = 1,
    .baseArrayLayer = 0,
    .layerCount = 1
};
