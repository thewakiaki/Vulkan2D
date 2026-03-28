cmake_minimum_required(VERSION 3.16)

add_compile_definitions(VULKAN_HPP_NO_STRUCT_CONSTRUCTORS)

project(Vulkan2D)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SDL3 REQUIRED)
find_package(glm REQUIRED)
find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/utilSrc/ErrorChecking.cpp
    src/utilSrc/VulkanHelpers/RequirementCheck.cpp
    src/utilSrc/VulkanHelpers/PDDetailExtraction.cpp
    src/utilSrc/VulkanHelpers/SwapchainHelper.cpp
    src/utilSrc/VulkanHelpers/CreateInfoHelper.cpp
    src/Game.cpp
    src/GameWindow.cpp
    src/VulkanCore.cpp
    src/VulkanComponents/VulkanInstance.cpp
    src/VulkanComponents/VulkanSurface.cpp
    src/VulkanComponents/VulkanPD.cpp
    src/VulkanComponents/VulkanLD.cpp
    src/VulkanComponents/VulkanSC.cpp
)

set(PCH_INCLUDE_HEADERS pch.h)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_INCLUDE_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_ROOT="${PROJECT_ROOT}")

target_link_libraries(${PROJECT_NAME}
    Vulkan::Vulkan
    fmt::fmt
    glfw
    SDL3::SDL3
    glm::glm
)
