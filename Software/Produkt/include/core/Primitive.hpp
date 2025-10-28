#pragma once
#include "core/HitComponent.hpp"

class Primitive : public HitComponent {
protected:
public:
    Primitive() = default;
    ~Primitive() = default;
    
  virtual bool Hit() const = 0;
};