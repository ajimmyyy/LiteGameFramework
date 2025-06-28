cmake_minimum_required(VERSION 3.31)
project(LiteGameFramework)

set(CMAKE_CXX_STANDARD 20)

# 若使用 MSVC，啟用警告等級
if (MSVC)
    add_compile_options(/W4)
endif()

# ───── 設定 FreeGLUT ─────
set(FREEGLUT_DIR "${CMAKE_SOURCE_DIR}/deps/freeglut")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(FREEGLUT_LIB_DIR "${FREEGLUT_DIR}/lib/x64")
else()
    set(FREEGLUT_LIB_DIR "${FREEGLUT_DIR}/lib")
endif()

include_directories(${FREEGLUT_DIR}/include)
link_directories(${FREEGLUT_LIB_DIR})

# ───── 設定 GLM ─────
set(GLM_DIR "${CMAKE_SOURCE_DIR}/deps/glm")
include_directories(${GLM_DIR})

# ───── 設定 stb_image ─────
set(STB_IMAGE_DIR "${CMAKE_SOURCE_DIR}/deps/stb")
include_directories(${STB_IMAGE_DIR})

# ───── 尋找 OpenGL ─────
find_package(OpenGL REQUIRED)

# ───── 主程式源碼 ─────
file(GLOB_RECURSE SOURCES
        "main.cpp"
        "src/**/*.cpp"
        "src/**/*.h"
)

# ───── 主程式 ─────
add_executable(LiteGameFramework ${SOURCES}
        include/Resources/IModelLoader.h
        include/Resources/ITextureLoader.h)

target_include_directories(LiteGameFramework PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${GLM_DIR}
)

target_link_libraries(LiteGameFramework
        ${OPENGL_gl_LIBRARY}
        freeglut.lib
)

add_custom_command(TARGET LiteGameFramework POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FREEGLUT_DIR}/bin/freeglut.dll"
        $<TARGET_FILE_DIR:LiteGameFramework>
)

# ───── 測試 ─────
# ───── 設定 Catch2 ─────
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

# ───── 設定 trompeloeil ─────
include(FetchContent)
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
        ${OPENGL_gl_LIBRARY}
        freeglut.lib
)

add_custom_command(TARGET ModelLoaderTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FREEGLUT_DIR}/bin/freeglut.dll"
        $<TARGET_FILE_DIR:ModelLoaderTest>
)