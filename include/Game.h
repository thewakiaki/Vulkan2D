#pragma once
#include "utils/ClassUitility.h"

class VulkanCore;
class GameWindow;

class Game : private ClassUtilities::ImmutableOwner<Game>{

public:
    Game(const VulkanCore& vulkan, const GameWindow& window);
    ~Game();

    bool StartGame();

    void Play();

private:
    bool mPlaying = false;

    const VulkanCore& mVulkan;
    const GameWindow& mWindow;
};
