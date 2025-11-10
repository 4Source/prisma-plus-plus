# Anleitung Clang, Cmake, Googletest
## Benutzte Guidelines und Standards
[Clang-Tidy Checks](https://clang.llvm.org/extra/clang-tidy/checks/list.html)

[LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html) 

[cppcoreguidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)  

modernize | bugprone | performance | cert | gsl | clang-analyzer

## Installation clang:
### Windows:
[Windows-Installer](https://github.com/llvm/llvm-project/releases)

### macOS:
```bash
brew install llvm
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
```
### Ubuntu:
```bash
sudo apt install gnupg lsb-release wget -y
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 17
sudo apt install clang-17 clang-tidy-17 clang-format-17
```
### Arch:
```bash
sudo pacman -S clang
```

## Cmake:
### Konfiguration (muss nur einmal ausgeführt werden!)
```bash
cmake build
```
## Build
```bash
cmake --build build
```

## Googletest
[Googletest](https://github.com/google/googletest)

Googletests wird beim clonen mit folgendem Aufruf automatisch als Submodul hinzugefügt.
```bash
git clone --recurse-submodules https://github.com/4Source/prisma-plus-plus.git
```

## Submodules
To update the submodules in already cloned repositories use:
```bash
git submodule update --recursive --remote
```
If the submodule gets not pulled check with 
```bash
git submodule status
```
if one submodule starts with ``-`` than do the following command to clone it
```bash
git submodule update --init path/to/submodule
```