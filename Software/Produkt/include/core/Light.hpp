#pragma once
#include "UUIDGenerator.hpp"
#include <glm/glm.hpp>
#include <string>
#include <uuid.h>

class Light {
  protected:
    uuids::uuid m_UUID;
    glm::vec3 m_Color{1.0};
    float m_Intensity{1.0};

  public:
    Light() : m_UUID{UUIDGenerator::gen()} {};

    Light(glm::vec3 color, float intensity) : m_UUID{UUIDGenerator::gen()}, m_Color{color}, m_Intensity{intensity} {}
    virtual ~Light() = default;

    glm::vec3 getColor() const { return m_Color; }
    void setColor(glm::vec3 color) { m_Color = color; }

    float getIntensity() const { return m_Intensity; }
    void setIntensity(float intensity) { m_Intensity = intensity; }

    virtual glm::vec3 getPosition() const = 0;
    virtual void setPosition(glm::vec3 pos) = 0;

    uuids::uuid getUUID() const { return m_UUID; }
    std::string getUUIDString() const { return uuids::to_string(m_UUID); }

    bool operator==(const Light &other) const { return m_UUID == other.m_UUID; }

    /**
     * @brief Gets a ray representing a light ray of this light source at a point in world space
     * @param worldPos The position in world space of the point on a object.
     * @return The Ray from this light source which comes from light position and goes to worldPos
     */
    virtual glm::vec3 getRay(const glm::vec3 worldPos) const = 0;
};
