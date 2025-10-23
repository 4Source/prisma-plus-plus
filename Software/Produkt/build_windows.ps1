# -----------------------------------------
# Build-Script with clang-tidy-Checks
# Build without tidy:
# .\build_windows.ps1 -no_tidy
# Build with tidy:
# .\build_windows.ps1
# -----------------------------------------

param(
    [Parameter(HelpMessage="Forces execution without clang-tidy checks")]
    [switch]$no_tidy = $false
)

Write-Host "Configure CMake..." -ForegroundColor Blue
cmake -S . -B build -G Ninja

if ($no_tidy -eq $false) {
    Write-Host "Running clang-tidy..." -ForegroundColor Blue
    $output = & .\run_clang_tidy.ps1 2>&1

    if ($output -match 'error:') {
        $output | Write-Host
        Write-Host "clang-tidy checks failed! Exit Build-Script" -ForegroundColor Red
        exit 1
    } else {
        Write-Host "clang-tidy checks completed" -ForegroundColor Green
    }
}

Write-Host "Running Build..." -ForegroundColor Blue
cmake --build build
