#include "GameWindow.h"

#include "utils/Constants.h"
#include "utils/ErrorChecking.h"

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

}

bool GameWindow::InitWindow(){

    fmt::print("Setting up Game Window\n");

    glfwInit();

    SetWindowHints();

    if(!CreateWindow()) { return false;}

    glfwShowWindow(mGameWindow);
    glfwFocusWindow(mGameWindow);

    fmt::print("Window Setup\n");

    return true;
}

void GameWindow::SetWindowHints(){
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

bool GameWindow::CreateWindow(){

    mGameWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Name", nullptr, nullptr);

    GlfwWindowCheck(mGameWindow, "Creation");

    return true;
}
