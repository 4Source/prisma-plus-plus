#pragma once
#include <core/Subray.h>
#include <stack>

class Ray {
  std::stack<Subray> subrays;

public:
  // Types must be changed
  Ray(Subray, int);
};