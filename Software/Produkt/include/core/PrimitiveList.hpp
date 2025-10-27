#pragma once
#include "core/Component.hpp"
#include <vector>

class PrimitiveList : public Component {
protected:
public:
  PrimitiveList() = default;
  ~PrimitiveList() = default;

  virtual bool Hit() const;
};