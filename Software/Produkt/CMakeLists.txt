# ------------------------------------------------------------------------------
# CMake Build File
# Description
# Configure with:
# cmake -S Software/Produkt -B Software/Produkt/build -G Ninja from Project Root
# for clang-tidy checks:
# cmake -S . -B Software/Produkt/build -G Ninja -DCHECK_CLANG=ON
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16)
project(prisma_pp LANGUAGES CXX)

# Always use Ninja and build inside ./build
if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
    message(STATUS "Switching to Ninja build system in ./build directory")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -G Ninja -S ${CMAKE_SOURCE_DIR} -B ${CMAKE_SOURCE_DIR}/build
    )
    message(FATAL_ERROR "Re-run cmake using Ninja in build directory!!")
endif()

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable exceptions
if(MSVC)
    add_compile_options(/EHsc)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-fexceptions)
endif()

# ------------------------------------------------------------------------------
# Optional clang-tidy
# Use -DCHECK_CLANG=ON or --check-clang
# ------------------------------------------------------------------------------
option(CHECK_CLANG "Enable clang-tidy checks" OFF)

if(CHECK_CLANG)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy enabled: ${CLANG_TIDY_EXE}")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "--format-style=file")
    else()
        message(WARNING "clang-tidy not found, disabling checks")
    endif()
else()
    message(STATUS "clang-tidy checks are disabled (use -DCHECK_CLANG=ON or --check-clang to enable)")
endif()

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
add_subdirectory(external/googletest)
add_subdirectory(external/glfw)

# Add include and src
include_directories(include)
add_library(firstcode src/firstcode.cpp)

# ImGui setup
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${glfw_SOURCE_DIR}/include
)

target_link_libraries(imgui PUBLIC glfw)

# ------------------------------------------------------------------------------
# Main executable
# ------------------------------------------------------------------------------
add_executable(prisma_pp 
    src/main.cpp
    src/ui/UIManager.cpp
    src/ui/MenuBar.cpp
)

if(APPLE)
    target_link_libraries(prisma_pp PRIVATE firstcode imgui
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
    )
elseif(WIN32)
    target_link_libraries(prisma_pp PRIVATE firstcode imgui opengl32)
elseif(UNIX)
    target_link_libraries(prisma_pp PRIVATE firstcode imgui GL X11 pthread dl)
endif()

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
add_executable(runTests tests/test_firstcode.cpp)
target_link_libraries(runTests PRIVATE gtest_main firstcode)

include(GoogleTest)
gtest_discover_tests(runTests)
