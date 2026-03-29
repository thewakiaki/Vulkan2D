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

find_program(GLSL_VALIDATOR glslangValidator HINTS $ENV{VULKAN_SDK}/bin)

set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Assets/Shaders")
set(SHADER_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Assets/Compiled/Shaders")

set(SHADER_SOURCES
    "${SHADER_SOURCE_DIR}/vert.glsl"
    "${SHADER_SOURCE_DIR}/frag.glsl"
)

foreach(SHADER_SOURCE ${SHADER_SOURCES})
    get_filename_component(FILE_NAME ${SHADER_SOURCE} NAME_WE)
    set(SPV_OUTPUT "${SHADER_OUTPUT_DIR}/${FILE_NAME}.spv")

    add_custom_command(
        OUTPUT ${SPV_OUTPUT}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_OUTPUT_DIR}
        COMMAND ${GLSL_VALIDATOR} -V -S ${FILE_NAME} ${SHADER_SOURCE} -o ${SPV_OUTPUT}
        DEPENDS ${SHADER_SOURCE}
        COMMENT "GLSL → SPIR-V: ${FILE_NAME}.glsl"
        VERBATIM
    )

    list(APPEND SPV_SHADERS ${SPV_OUTPUT})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SPV_SHADERS})

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/utilSrc/ErrorChecking.cpp
    src/utilSrc/FileHandling.cpp
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
    src/VulkanComponents/VulkanSM.cpp
)

add_dependencies(${PROJECT_NAME} Shaders)

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
