$basePath = Split-Path -Parent $MyInvocation.MyCommand.Path
$folders = @("src", "tests")
$exit_code = 0

foreach ($f in $folders) {
    $fullPath = Join-Path $basePath $f
    Get-ChildItem -Path $fullPath -Recurse -Include *.cpp -File | ForEach-Object -Parallel {
        clang-tidy $_.FullName --p="$basePath/build"
        if ($LASTEXITCODE -ne 0) {
            $exit_code = $LASTEXITCODE
        }
    } -ThrottleLimit 8
}
exit $exit_code