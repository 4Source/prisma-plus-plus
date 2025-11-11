#include "cli/CliManager.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdint>
//#include <optionparser.h>

/// @brief
/// @param argc
/// @param argv
/// @return
int main(int argc, char *argv[]) { // NOLINT
    try {
        std::cout << "Hello Prisma++" << "\n";
        //std::cout << "Add-Lib: " << add(1, 2) << "\n";

		return CliManager::run({argv, static_cast<size_t>(argc)});

    } catch (const std::exception &e) {
        std::cerr << "FATAL: " << e.what() << "\n";
    }
    return 1;
}

auto test() -> int
{
    return 1;
}
