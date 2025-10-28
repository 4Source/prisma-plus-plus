#include "firstcode.h"
#include "Domain/Resolution.h"
#include "Domain/Subray.h"
#include <glm/vec3.hpp>
#include <iostream>

auto add(int a, int b) -> int {
  Subray sr = Subray();
  sr.direction = glm::vec3(1.0f, 0.0f, 0.0f);
  Resolution res = Resolution::high;
  std::cout << "Resolution is \n" << static_cast<int>(res) << "\n";
  return a + b;
}
