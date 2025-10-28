#pragma once
#include "core/HitComponent.hpp"
#include <array>
#include <memory>

class HitComponentOctree : public HitComponent {
private:
  std::array<std::unique_ptr<HitComponent>, 8> m_Children;

public:
  HitComponentOctree() = default;
  ~HitComponentOctree() = default;

  virtual bool Hit() const override;
  virtual void Add(HitComponent &in) override;
  virtual void Remove(HitComponent &in) override;
};