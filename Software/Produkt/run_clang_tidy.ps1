$folders = @("src", "tests")
foreach ($f in $folders) {
    Get-ChildItem -Path $f -Recurse -Include *.cpp -File | ForEach-Object {
        clang-tidy $_.FullName --p=build
    }
}
