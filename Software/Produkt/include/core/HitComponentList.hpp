#pragma once
#include "core/HitComponent.hpp"
#include <memory>
#include <string>
#include <vector>

class HitComponentList : public HitComponent {
  private:
    std::vector<std::unique_ptr<HitComponent>> m_Children;

  public:
    HitComponentList() = default;
    virtual ~HitComponentList() = default;

    virtual bool Hit() const override;
    virtual void Add(HitComponent &in) override;
    virtual void Remove(HitComponent &in) override;

    virtual std::string toString() override;
};