#pragma once
#include <memory>
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
    virtual std::string toString() { return "uuid: " + uuids::to_string(m_UUID); };
};