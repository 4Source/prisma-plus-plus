#pragma once
#include <core/HitComponent.hpp>
#include <core/Light.hpp>
#include <core/Subray.hpp>
#include <stack>

class Ray {
    std::stack<Subray> subrays;

  public:
    // Call by referece for HitComponent and Light objects
    Ray(Subray, HitComponent &, std::span<Light>);
};