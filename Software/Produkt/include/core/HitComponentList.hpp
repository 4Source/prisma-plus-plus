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
    virtual ~HitComponentList() = default;

    size_t size() const { return m_Children.size(); }

    virtual bool hit() const override;
    virtual void add(std::shared_ptr<HitComponent> component) override;
    virtual void remove(std::shared_ptr<HitComponent> component) override;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) override;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) override;

    virtual std::string toString() override;
};