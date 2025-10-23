$folders = @("src","include","tests")
foreach ($f in $folders) {
    Get-ChildItem -Path $f -Recurse -Include *.cpp,*.h -File | ForEach-Object {
        clang-tidy $_.FullName --p=build
    }
}
