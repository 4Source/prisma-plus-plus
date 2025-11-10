#pragma once
#include <core/Subray.hpp>
#include <stack>
#include <core/HitComponent.hpp>
#include <core/Light.hpp>

class Ray {
  std::stack<Subray> subrays;

public:
// Call by referece for HitComponent and Light objects
  Ray(Subray, HitComponent&, std::span<Light>);
};