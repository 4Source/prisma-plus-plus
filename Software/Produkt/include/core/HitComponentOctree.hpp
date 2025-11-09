#pragma once
#include "core/HitComponent.hpp"
#include <array>
#include <memory>
#include <string>

class HitComponentOctree : public HitComponent {
  private:
    std::array<std::shared_ptr<HitComponent>, 8> m_Children;

  public:
    HitComponentOctree() = default;
    virtual ~HitComponentOctree() = default;

    virtual bool hit() const override;
    virtual void add(std::shared_ptr<HitComponent> component) override;
    virtual void remove(std::shared_ptr<HitComponent> component) override;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) override;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) override;

    virtual std::string toString() override;
};