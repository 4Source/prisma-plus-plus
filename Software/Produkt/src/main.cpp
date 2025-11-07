#include "cli/CliManager.h"
#include <iostream>

/// @brief
/// @param argc
/// @param argv
/// @return
int main(int argc, char *argv[]) { // NOLINT
    try {
        return CliManager::run({argv, static_cast<size_t>(argc)});
    } catch (const std::exception &e) {
        std::cerr << "FATAL: " << e.what() << "\n";
    }
    return 1;
}
