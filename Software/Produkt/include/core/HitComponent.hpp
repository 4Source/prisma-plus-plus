#pragma once
#include <memory>
#include <string>
#include <uuid.h>
#include "core/Hit.hpp"
#include "core/Subray.hpp"

class HitComponent {
  protected:
    uuids::uuid m_UUID;

  public:
    HitComponent();
    virtual ~HitComponent() = default;

    HitComponent(const HitComponent &) = delete;
    HitComponent &operator=(const HitComponent &) = delete;

    HitComponent(HitComponent &&) noexcept = delete;
    HitComponent &operator=(HitComponent &&) noexcept = delete;

    uuids::uuid getUUID() const { return m_UUID; }
    std::string getUUIDString() const { return uuids::to_string(m_UUID); }

    virtual Hit hit(const Subray& s) const = 0;
    virtual void add(std::shared_ptr<HitComponent> component) = 0;
    virtual void remove(std::shared_ptr<HitComponent> component) = 0;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) = 0;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) = 0;

    bool operator==(const HitComponent &other) const { return m_UUID == other.m_UUID; }
    virtual std::string toString() { return "uuid: " + uuids::to_string(m_UUID); };
};
