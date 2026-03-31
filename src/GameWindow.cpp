#include "GameWindow.h"

#include "utils/Constants.h"
#include "utils/ErrorChecking.h"
#include "VulkanCore.h"

using namespace ErrorChecking;

GameWindow::GameWindow(){
    mGameWindow = nullptr;
}

GameWindow::~GameWindow(){

    if(mGameWindow)
    {
        glfwDestroyWindow(mGameWindow);
        mGameWindow = nullptr;
    }

    if(mVulkan){
        mVulkan = nullptr;
    }

}

bool GameWindow::InitWindow(){

    fmt::print("Setting up Game Window\n");

    glfwInit();

    SetWindowHints();

    if(!CreateWindow()) { return false;}

    glfwSetWindowUserPointer(mGameWindow, this);
    glfwSetFramebufferSizeCallback(mGameWindow, FrameBufferResizeCallback);

    fmt::print("Window Setup\n");

    return true;
}

void GameWindow::SetWindowHints(){
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
}

bool GameWindow::CreateWindow(){

    mGameWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Name", nullptr, nullptr);

    GlfwWindowCheck(mGameWindow, "Creation");

    return true;
}

void GameWindow::FrameBufferResizeCallback(GLFWwindow *window, int width, int height){

    auto self = static_cast<GameWindow*>(glfwGetWindowUserPointer(window));

    if(self){ self->mVulkan->ToggleFrameBufferResize(); }
}
