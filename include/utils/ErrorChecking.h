#pragma once

namespace ErrorChecking {

    bool GlfwWindowCheck(GLFWwindow* window, const char* errorContext);

    bool VkResultCheck(VkResult& result, const char* checkComponent);

}
