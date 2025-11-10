#pragma once
#include "UUIDGenerator.hpp"
#include <memory>
#include <string>
#include <uuid.h>

class HitComponent {
  protected:
    uuids::uuid m_UUID;

  public:
    HitComponent() : m_UUID{UUIDGenerator::gen()} {};
    virtual ~HitComponent() = default;

    HitComponent(const HitComponent &) = delete;
    HitComponent &operator=(const HitComponent &) = delete;

    HitComponent(HitComponent &&) noexcept = delete;
    HitComponent &operator=(HitComponent &&) noexcept = delete;

    uuids::uuid getUUID() const { return m_UUID; }
    std::string getUUIDString() const { return uuids::to_string(m_UUID); }

    virtual bool hit() const = 0;
    virtual void add(std::shared_ptr<HitComponent> component) = 0;
    virtual void remove(std::shared_ptr<HitComponent> component) = 0;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) = 0;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) = 0;

    bool operator==(const HitComponent &other) const { return m_UUID == other.m_UUID; }
    virtual std::string toString(bool formatted = false, int indentLevel = 0) {
        return "uuid: " + uuids::to_string(m_UUID) + (formatted ? std::string("\n") : std::string(" "));
    };
};