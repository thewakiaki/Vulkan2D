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

constexpr std::array<std::pair<uint32_t, const char*>, 5> API_VERSIONS = {{
    {VK_API_VERSION_1_0, "VULKAN API VERSION 1.0"},
    {VK_API_VERSION_1_1, "VULKAN API VERSION 1.1"},
    {VK_API_VERSION_1_2, "VULKAN API VERSION 1.2"},
    {VK_API_VERSION_1_3, "VULKAN API VERSION 1.3"},
    {VK_API_VERSION_1_4, "VULKAN API VERSION 1.4"}
}};
