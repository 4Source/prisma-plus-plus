#pragma once
#include "core/HitComponent.hpp"
#include <memory>

class Primitive : public HitComponent, public std::enable_shared_from_this<Primitive> {
  protected:
  public:
    Primitive() = default;
    virtual ~Primitive() = default;

    virtual void add(std::shared_ptr<HitComponent> component) override;
    virtual void remove(std::shared_ptr<HitComponent> component) override;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) override;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) override;
};
