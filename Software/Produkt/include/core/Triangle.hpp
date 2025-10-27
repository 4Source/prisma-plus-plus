#pragma once
#include "core/Primitive.hpp"
#include <glm/glm.hpp>

class Triangle : public Primitive {
private:
  size_t *indices = new size_t[3];

public:
  Triangle() = default;
  ~Triangle() { delete[] indices; };

  virtual bool Hit() const override;
};