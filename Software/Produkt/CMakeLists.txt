# ------------------------------------------------------------------------------
# CMake Build File
# Description
# Configure with:
# cmake -S Software/Produkt -B Software/Produkt/build -G Ninja from Project Root
# for clang-tidy checks:
# cmake -S Software/Produkt -B Software/Produkt/build -G Ninja -DCHECK_CLANG=ON
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16)
project(prisma-plus-plus LANGUAGES CXX)

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
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/googletest)

# ------------------------------------------------------------------------------
# ImGui setup
# ------------------------------------------------------------------------------
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
# Core library from sources
# ------------------------------------------------------------------------------
# Grab all .cpp files in src/
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Remove main.cpp from the list
list(FILTER SRC_FILES EXCLUDE REGEX ".*main\\.cpp$")

# Print the resulting list
message(STATUS "Source files for prisma-core:")
foreach(f ${SRC_FILES})
    message(STATUS "  ${f}")
endforeach()

add_library(prisma-core STATIC ${SRC_FILES})
# ------------------------------------------------------------------------------
# Add Library Folders include and ecternal/optionparser
# ------------------------------------------------------------------------------
target_include_directories(prisma-core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/optionparser
)
target_link_libraries(prisma-core PUBLIC imgui)
target_link_libraries(prisma-core PUBLIC glm)

if(APPLE)
    target_link_libraries(prisma-core PUBLIC "-framework OpenGL")
    target_link_libraries(prisma-core PUBLIC "-framework Cocoa")
    target_link_libraries(prisma-core PUBLIC "-framework IOKit")
    target_link_libraries(prisma-core PUBLIC "-framework CoreFoundation")
elseif(WIN32)
    target_link_libraries(prisma-core PUBLIC opengl32)
elseif(UNIX)
    target_link_libraries(prisma-core PUBLIC GL)
    target_link_libraries(prisma-core PUBLIC X11)
    target_link_libraries(prisma-core PUBLIC pthread)
    target_link_libraries(prisma-core PUBLIC dl)
endif()

# ------------------------------------------------------------------------------
# Main executable
# ------------------------------------------------------------------------------
add_executable(prisma-plus-plus 
    src/main.cpp
)

target_link_libraries(prisma-plus-plus PRIVATE prisma-core)
# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
include(GoogleTest)

# Add all your test and related source files (recursively if desired)
file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

# Print the resulting list
message(STATUS "Test files for runTests:")
foreach(f ${TEST_FILES})
    message(STATUS "  ${f}")
endforeach()

add_executable(runTests ${TEST_FILES})

target_link_libraries(runTests PRIVATE gtest_main)
target_link_libraries(runTests PRIVATE prisma-core)

enable_testing()
gtest_discover_tests(runTests)
