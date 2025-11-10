#pragma once
#include <core/Subray.hpp>
#include <stack>
#include <core/HitComponent.hpp>

class Ray {
  std::stack<Subray> subrays;

public:
  // Types must be changed
  Ray(Subray, HitComponent);
};