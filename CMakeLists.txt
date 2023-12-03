cmake_minimum_required(VERSION 3.20)
project(mock-engine LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(stb GIT_REPOSITORY https://github.com/nothings/stb.git)
FetchContent_MakeAvailable(stb)

set (SOURCES src/Input.cpp src/RenderCtx.cpp)

add_executable(mock-engine src/main_functional.cpp ${SOURCES})
target_include_directories(mock-engine PRIVATE include/ ${glfw_SOURCE_DIR}/include/ ${glm_SOURCE_DIR}/ ${stb_SOURCE_DIR})

set_property(TARGET mock-engine PROPERTY CXX_STANDARD 20)
set_property(TARGET mock-engine PROPERTY C_STANDARD 20)
