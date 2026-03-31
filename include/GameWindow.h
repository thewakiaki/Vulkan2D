#pragma once

#include "utils/ClassUitility.h"

class VulkanCore;

class GameWindow : private ClassUtilities::ImmutableOwner<GameWindow>{

public:
    GameWindow();
    ~GameWindow();

    bool InitWindow();

    GLFWwindow* GetWindow() const { return mGameWindow; }

    static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);

    void SetVulkanCore(VulkanCore* vulkan) { mVulkan = vulkan; }

private:
    void SetWindowHints();

    bool CreateWindow();

    GLFWwindow* mGameWindow;

    VulkanCore* mVulkan = nullptr;
};
