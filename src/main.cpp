#include "Game.h"
#include "VulkanCore.h"
#include "GameWindow.h"

int main() {
    try {
        GameWindow window;

        if(!window.InitWindow()){
            fmt::print("Failed to setup game window\n");
            return EXIT_FAILURE;
        }

        VulkanCore vulkan(window);
        if (!vulkan.InitVulkan()) {
            fmt::print("Failed to initialise Vulkan\n");
            return EXIT_FAILURE;
        }

        Game game(vulkan, window);
        game.StartGame();

    } catch (const vk::SystemError& e) {\
        glfwTerminate();
        fmt::print("Vulkan error: {}\n", e.what());
        return EXIT_FAILURE;

    } catch (const std::exception& e) {
        glfwTerminate();
        fmt::print("Runtime error: {}\n", e.what());
        return EXIT_FAILURE;

    }

    glfwTerminate();
    fmt::print("Game closed successfully\n");
    return EXIT_SUCCESS;
}
