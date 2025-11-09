#pragma once
#include <string>
#include <uuid.h>

class HitComponent {
  protected:
    uuids::uuid m_UUID;

  public:
    HitComponent() : m_UUID{uuids::uuid_system_generator{}()} {};
    virtual ~HitComponent() = default;

    HitComponent(const HitComponent &) = delete;
    HitComponent &operator=(const HitComponent &) = delete;

    HitComponent(HitComponent &&) noexcept = delete;;
    HitComponent &operator=(HitComponent &&) noexcept = delete;

    uuids::uuid getUUID() const { return m_UUID; }
    std::string getUUIDString() const { return uuids::to_string(m_UUID); }

    virtual bool hit() const = 0;
    virtual void add(HitComponent &in) {}
    virtual void remove(HitComponent &in) {}

    bool operator==(const HitComponent &other) const { return m_UUID == other.m_UUID; }
    virtual std::string toString() { return "uuid: " + uuids::to_string(m_UUID); };
};