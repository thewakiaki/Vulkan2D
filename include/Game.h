#pragma once
#include "utils/ClassUitility.h"

class VulkanCore;
class GameWindow;

class Game : private ClassUtilities::ImmutableOwner<Game>{

public:
    Game(VulkanCore& vulkan, GameWindow& window);
    ~Game();

    bool StartGame();

    void Play();

private:
    bool mPlaying = false;

    VulkanCore& mVulkan;
    GameWindow& mWindow;
};
