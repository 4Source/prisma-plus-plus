#include <iostream>
#include <stdexcept>
#include <firstcode.h>

auto main() -> int { // NOLINT(bugprone-exception-escape)
    try {
        std::cout << "Hello Prisma++" << "\n";
        std::cout << "Add-Lib: " << add(1,2) << "\n";
        
        return 0;
    }
    catch (const std::exception& e) {
        // Handle it internally to prevent it from escaping.
        // Note: I/O itself can still throw, but this is the intent.
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "ERROR: Unknown exception caught." << "\n";
    }

    // Since we caught the exception, we can still exit cleanly with an error code.
    return 1; 
}

auto test() -> int
{
    return 1;
}