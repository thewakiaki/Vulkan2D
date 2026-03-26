#pragma once

#include "utils/ClassUitility.h"

class GameWindow : private ClassUtilities::ImmutableOwner<GameWindow>{

public:
    GameWindow();
    ~GameWindow();

    bool InitWindow();

    GLFWwindow* GetWindow() const { return mGameWindow; }

private:
    void SetWindowHints();

    bool CreateWindow();

    GLFWwindow* mGameWindow;
};
