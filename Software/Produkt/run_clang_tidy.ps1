$basePath = Split-Path -Parent $MyInvocation.MyCommand.Path
$folders = @("src", "tests")

foreach ($f in $folders) {
    $fullPath = Join-Path $basePath $f
    Get-ChildItem -Path $fullPath -Recurse -Include *.cpp -File | ForEach-Object {
        clang-tidy $_.FullName --p="$basePath/build"
    }
}

