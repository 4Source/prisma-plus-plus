#!/usr/bin/env bash
# -----------------------------------------
# Build-Script with clang-tidy-Checks
# Build without tidy:
# .\build_windows.ps1 --no_tidy
# Build with tidy:
# .\build_windows.ps1
# -----------------------------------------

set -e

NO_TIDY=false
for arg in "$@"; do
    if [[ "$arg" == "--no-tidy" ]]; then
        NO_TIDY=true
    fi
done

echo -e "\033[34mConfigure CMake...\033[0m"
cmake -S . -B build -G Ninja

if [ "$NO_TIDY" = false ]; then
    echo -e "\033[34mRunning clang-tidy...\033[0m"
    output=$(./run_clang_tidy.sh 2>&1)

    if echo "$output" | grep -q "error:"; then
        echo "$output"
        echo -e "\033[31mclang-tidy checks failed! Exit build script.\033[0m"
        exit 1
    else
        echo -e "\033[32mclang-tidy checks completed.\033[0m"
    fi
fi

echo -e "\033[34mRunning build...\033[0m"
cmake --build build
