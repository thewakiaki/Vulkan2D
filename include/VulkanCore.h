#pragma once
#include "utils/ClassUitility.h"
#include "utils/VulkanStructs.h"

class GameWindow;
class VulkanInstance;
class VulkanSurface;
class VulkanPD;
class VulkanLD;
class VulkanSC;
class VulkanGP;
class VulkanCmdPool;
class VulkanRenderer;
class VulkanVBuffer;

class VulkanCore : private ClassUtilities::ImmutableOwner<VulkanCore>{

public:
    VulkanCore(GameWindow& window);
    ~VulkanCore();

    bool InitVulkan();

    bool DrawFrame();

    void ToggleFrameBufferResize();
    const VulkanLD& GetLogicalDevice() const { return *mLogicalDevice; }
    const bool& GetFatalError() const;

private:
    void SetRequirements();
    void AddGlfwExtensions(std::vector<const char*>& required);

    std::unique_ptr<VulkanInstance> mInstance;
    std::unique_ptr<VulkanSurface> mSurface;
    std::unique_ptr<VulkanPD> mPhysicalDevice;
    std::unique_ptr<VulkanLD> mLogicalDevice;
    std::unique_ptr<VulkanSC> mSwapchain;
    std::unique_ptr<VulkanGP> mGraphicsPipeline;
    std::unique_ptr<VulkanCmdPool> mCommandPool;
    std::unique_ptr<VulkanVBuffer> mVertexBuffer;
    std::unique_ptr<VulkanRenderer> mRenderer;

    VulkanStructs::VulkanRequirements mVulkanRequirements;

    GameWindow& mGameWindow;


    const std::vector<VulkanStructs::Vertex> vertices = {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };
};
