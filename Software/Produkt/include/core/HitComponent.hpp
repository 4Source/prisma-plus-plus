#pragma once
#include <string>
#include <uuid.h>

class HitComponent {
  protected:
    uuids::uuid m_UUID;

  public:
    HitComponent() : m_UUID{uuids::uuid_system_generator{}()} {};
    virtual ~HitComponent() = default;

    HitComponent(const HitComponent &) : m_UUID{uuids::uuid_system_generator{}()} {}
    HitComponent &operator=(const HitComponent &) {
        m_UUID = uuids::uuid_system_generator{}();
        return *this;
    }

    HitComponent(HitComponent &&) noexcept = default;
    HitComponent &operator=(HitComponent &&) noexcept = default;

    uuids::uuid getUUID() const { return m_UUID; }
    std::string getUUIDString() const { return uuids::to_string(m_UUID); }

    virtual bool Hit() const = 0;
    virtual void Add(HitComponent &in) {}
    virtual void Remove(HitComponent &in) {}

    bool operator==(const HitComponent &other) const { return m_UUID == other.m_UUID; }
    virtual std::string toString() { return "uuid: " + uuids::to_string(m_UUID); };
};