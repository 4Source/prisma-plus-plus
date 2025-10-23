$folders = @("src","include","tests")
foreach ($f in $folders) {
             Get-ChildItem $f -Recurse -Include *.cpp | ForEach-Object {
                 clang-tidy $_.FullName --p=build
             }
         }
