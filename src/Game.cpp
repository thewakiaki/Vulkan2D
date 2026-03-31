#include "Game.h"

#include "VulkanCore.h"
#include "GameWindow.h"
#include "VulkanComponents/VulkanLD.h"

Game::Game(VulkanCore& vulkan, GameWindow& window) : mVulkan(vulkan), mWindow(window){

}

Game::~Game(){

}

bool Game::StartGame(){

    fmt::print("Game Starting\n");

    mPlaying = true;

    Play();

    return true;
}

void Game::Play(){

    fmt::print("----------------------\n");
    fmt::print("Game Running\n");

    while(mPlaying && !glfwWindowShouldClose(mWindow.GetWindow()) && !mVulkan.GetFatalError()){
        fmt::print("New Frame\n");
        glfwPollEvents();

        if (glfwGetKey(mWindow.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mPlaying = false;
            fmt::print("Escape pressed\n");
        }

        if(!mVulkan.DrawFrame()) { fmt::print("Skipping Frame\n"); }
    }

    fmt::print("Game Ending\n");

    vkDeviceWaitIdle(mVulkan.GetLogicalDevice().GetLogicalDevice());
}
