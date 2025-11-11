#pragma once
#include "core/HitComponent.hpp"
#include <array>
#include <memory>
#include <string>

class HitComponentOctree : public HitComponent {
  private:
    std::array<std::shared_ptr<HitComponent>, 8> m_Children;

  public:
    HitComponentOctree() = delete;
	  HitComponentOctree(HitComponentOctree&&) noexcept = delete;
    HitComponentOctree& operator=(HitComponentOctree&&) noexcept = delete;
    HitComponentOctree(const HitComponentOctree&) = delete;
    HitComponentOctree& operator=(const HitComponentOctree&) = delete;
    virtual ~HitComponentOctree() = default;

    virtual Hit hit(const Subray& s) const override;
    virtual void add(std::shared_ptr<HitComponent> component) override;
    virtual void remove(std::shared_ptr<HitComponent> component) override;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) override;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) override;

    virtual std::string toString(bool formatted = false, int indentLevel = 0) override;
};
