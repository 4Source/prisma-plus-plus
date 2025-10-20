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
	add_subdirectory(googletest)
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


add_subdirectory(googletest)

# Add include and src
include_directories(include)
add_library(firstcode src/firstcode.cpp)

# Main executable
add_executable(prisma_pp src/main.cpp)
target_link_libraries(prisma_pp firstcode)

# Test executable
#find_package(GTest REQUIRED)
add_executable(runTests tests/test_firstcode.cpp)
target_link_libraries(runTests PRIVATE gtest_main firstcode)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(runTests)
