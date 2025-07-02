cmake_minimum_required(VERSION 3.31)
project(LiteGameFramework)

set(CMAKE_CXX_STANDARD 20)

# 若使用 MSVC，啟用警告等級
if (MSVC)
    add_compile_options(/W4)
endif()

# ───── 加入 GLFW ─────
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# ───── 設定 GLM ─────
set(GLM_DIR "${CMAKE_SOURCE_DIR}/deps/glm")
include_directories(${GLM_DIR})

# ───── 加入 glad ─────
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/deps/glad")
add_subdirectory(deps/glad)

# ───── 設定 stb_image ─────
set(STB_IMAGE_DIR "${CMAKE_SOURCE_DIR}/deps/stb")
include_directories(${STB_IMAGE_DIR})

# ───── 設定 json ─────
set(JSON_DIR "${CMAKE_SOURCE_DIR}/deps/nlohmann")
include_directories(${JSON_DIR})

# ───── 尋找 OpenGL ─────
find_package(OpenGL REQUIRED)

# ───── 主程式源碼 ─────
file(GLOB_RECURSE SOURCES
        "main.cpp"
        "src/**/*.cpp"
        "src/**/*.h"
)

# ───── 主程式 ─────
add_executable(LiteGameFramework ${SOURCES})

target_include_directories(LiteGameFramework PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${GLM_DIR}
        ${STB_IMAGE_DIR}
        ${glfw_SOURCE_DIR}/include
        ${GLAD_DIR}/include
        ${JSON_DIR}
)

target_link_libraries(LiteGameFramework
        glfw
        glad
        ${OPENGL_gl_LIBRARY}
)

# ───── 測試 ─────
# ───── 設定 Catch2 ─────
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

# ───── 設定 trompeloeil ─────
FetchContent_Declare(
        trompeloeil
        GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
        GIT_TAG v49
)
FetchContent_MakeAvailable(trompeloeil)

add_executable(ModelLoaderTest
        src/Resources/ResourceManager.cpp
        src/Resources/ModelLoader.cpp
        src/Platform/FileSystem.cpp
        tests/Resources/ModelLoaderTest.cpp
        tests/Resources/ResourceManagerTest.cpp
        tests/Resources/MockModelLoader.h
        tests/Resources/MockTextureLoader.h
)

target_include_directories(ModelLoaderTest PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${GLM_DIR}
)

target_link_libraries(ModelLoaderTest
        Catch2::Catch2WithMain
        trompeloeil
        glfw
        glad
        ${OPENGL_gl_LIBRARY}
)