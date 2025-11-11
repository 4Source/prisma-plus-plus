#pragma once
#include "core/HitComponent.hpp"
#include <memory>
#include <string>
#include <vector>

class HitComponentList : public HitComponent {
  private:
    std::vector<std::shared_ptr<HitComponent>> m_Children;

  public:
    HitComponentList() = default;
	  HitComponentList(HitComponentList&&) noexcept = default;
    HitComponentList& operator=(HitComponentList&&) noexcept = default;
    HitComponentList(const HitComponentList&) = delete;
    HitComponentList& operator=(const HitComponentList&) = delete;
    virtual ~HitComponentList() = default;

    size_t size() const { return m_Children.size(); }

    virtual Hit hit(const Subray& s) const override;
    virtual void add(std::shared_ptr<HitComponent> component) override;
    virtual void remove(std::shared_ptr<HitComponent> component) override;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) override;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) override;

    virtual std::string toString(bool formatted = false, int indentLevel = 0) override;
};
