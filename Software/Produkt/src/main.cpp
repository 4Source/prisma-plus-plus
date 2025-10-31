#include "ui/UIManager.h"
#include <core/Ray.h>
#include <core/Resolution.h>
#include <core/Subray.h>
#include <iostream>
#include <stdexcept>

auto test() -> int { return 1; }
auto main() -> int { // NOLINT(bugprone-exception-escape)
  try {

    std::cout << "Hello Prisma++" << "\n";
    std::cout << "Add-Lib: " << "\n";
    Subray s1{};
    s1.setDirection(glm::vec3(1.0f, 0.0f, 0.0f));
    s1.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    s1.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
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
