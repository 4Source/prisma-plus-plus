#pragma once
#include "core/Component.hpp"

class Primitive : public Component {
protected:
public:
    Primitive() = default;
    ~Primitive() = default;
    
  virtual bool Hit() const = 0;
};