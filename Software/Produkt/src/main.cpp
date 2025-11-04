#include "cli/CliManager.h"
#include "ui/UIManager.h"
#include <iostream>

int main(int argc, const char* argv[]) { // NOLINT
    try {
        if (/* detect GUI mode */ false) {
            UIManager
            return UIManager::run();
        }
        return CliManager::run(argc, argv);

    } catch (const std::exception& e) {
        std::cerr << "FATAL: " << e.what() << "\n";
    }
    return 1;
}
