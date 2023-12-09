cmake_minimum_required(VERSION 3.20)
project(mock-engine LANGUAGES C CXX)
add_compile_options(-ggdb)
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
  FetchContent_Populate(glad)
  set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
  set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
  set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
  add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.x)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(stb GIT_REPOSITORY https://github.com/nothings/stb.git)
FetchContent_MakeAvailable(stb)

set (SOURCES 
	src/Util.cpp
	src/Test/PlayerEntity.cpp
	src/Scene.cpp
	src/Logger.cpp
	src/Shader.cpp
	src/Texture.cpp
	src/TextureAtlas.cpp
	src/Resource.cpp
	src/ResourceManager.cpp
	src/Engine.cpp
	src/Input.cpp
	src/App.cpp
	src/RenderCtx.cpp)

add_executable(mock-engine src/main_functional.cpp ${SOURCES})
target_include_directories(mock-engine PRIVATE include/ ${glfw_SOURCE_DIR}/include/ ${glm_SOURCE_DIR}/ ${stb_SOURCE_DIR} ${spdlog_SOURCE_DIR}/include/spdlog)
target_link_libraries(mock-engine glfw glad glm spdlog)

set_property(TARGET mock-engine PROPERTY CXX_STANDARD 20)
set_property(TARGET mock-engine PROPERTY C_STANDARD 20)
