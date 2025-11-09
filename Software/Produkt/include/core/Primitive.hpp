#pragma once
#include "core/HitComponent.hpp"

class Primitive : public HitComponent {
  protected:
  public:
    Primitive() = default;
    virtual ~Primitive() = default;

    virtual bool hit() const = 0;
};