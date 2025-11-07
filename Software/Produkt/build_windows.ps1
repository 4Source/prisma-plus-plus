# -----------------------------------------
# Build-Script with clang-tidy Checks
# Usage:
#   .\build_windows.ps1         -> Build with clang-tidy
#   .\build_windows.ps1 -no_tidy -> Build without clang-tidy
# -----------------------------------------

param(
    [switch]$no_tidy = $false
)

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $ScriptDir

Write-Host "Configure CMake..." -ForegroundColor Blue
cmake -S . -B build -G Ninja

if (-not $no_tidy) {
    Write-Host "Running clang-tidy..." -ForegroundColor Blue
    $output = & "$ScriptDir\run_clang_tidy.ps1" 2>&1

    if ($output -match 'error:') {
        $output | Write-Host
        Write-Host "clang-tidy checks failed! Exit Build-Script" -ForegroundColor Red
        exit 1
    } else {
        Write-Host "clang-tidy checks completed" -ForegroundColor Green
    }
}

Write-Host "Running Build..." -ForegroundColor Blue
cmake --build "$ScriptDir\build"
exit $LASTEXITCODE