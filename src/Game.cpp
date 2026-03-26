#include "Game.h"

#include "VulkanCore.h"
#include "GameWindow.h"

Game::Game(const VulkanCore& vulkan, const GameWindow& window) : mVulkan(vulkan), mWindow(window){

}

Game::~Game(){

}

bool Game::StartGame(){

    fmt::print("Game Starting\n");

    mPlaying = true;

    //Play();

    return true;
}

void Game::Play(){

    while(mPlaying && !glfwWindowShouldClose(mWindow.GetWindow())){
        glfwPollEvents();

        if (glfwGetKey(mWindow.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mPlaying = false;
        }
    }
}
