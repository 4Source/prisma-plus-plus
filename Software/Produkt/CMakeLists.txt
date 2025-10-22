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
# Generate compile_commands.json (clang tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Activate Exceptions for Windows
if(MSVC)
    # MSVC oder clang-cl auf Windows
    add_compile_options(/EHsc)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    # Clang oder GCC auf Linux/macOS
    add_compile_options(-fexceptions)
endif()


if(APPLE)
	# macOS: deactivate clang-tidy
	set(CMAKE_CXX_CLANG_TIDY "")
else()
	# Other systems: clang-tidy
	# Check for clang-tidy 
	# No tidy -> no build :)
	find_program(CLANG_TIDY_EXE NAMES clang-tidy)
	if(CLANG_TIDY_EXE)
	    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
	    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "--format-style=file")    
	    message(STATUS "Clang-Tidy enabled. Configuration via .clang-tidy")
	else()
	    message(FATAL_ERROR "clang-tidy not found!!")
	endif()
endif()

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

# Main executable
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

# Test executable
add_executable(runTests tests/test_firstcode.cpp)
target_link_libraries(runTests PRIVATE gtest_main firstcode)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(runTests)
