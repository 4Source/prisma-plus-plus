#include "ui/UIManager.h"
#include <core/Ray.hpp>
#include <core/Resolution.hpp>
#include <core/Subray.hpp>
#include <iostream>
#include <stdexcept>

auto test() -> int { return 1; }
auto main() -> int { // NOLINT(bugprone-exception-escape)
  try {

    std::cout << "Hello Prisma++" << "\n";
    std::cout << "Add-Lib: " << "\n";
    Subray s1 = {.direction_ = {1.0f, 0.0f, 0.0f},
                 .position_ = {0.0f, 0.0f, 0.0f},
                 .color_ = {1.0f, 1.0f, 1.0f}};
    Ray r1{s1, test()};
    //  create window
    UIManager ui(800, 600, "Prisma++"); // NOLINT
    ui.run();                           // run main UI loop
    return 0;
  } catch (const std::exception &e) {
    // Handle it internally to prevent it from escaping.
    // Note: I/O itself can still throw, but this is the intent.
    std::cerr << "ERROR: " << e.what() << "\n";
  } catch (...) {
    std::cerr << "ERROR: Unknown exception caught." << "\n";
  }

  // Since we caught the exception, we can still exit cleanly with an error
  // code.
  return 1;
}
