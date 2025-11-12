#pragma once

#include <glm/glm.hpp>

class Light {
  protected:
    glm::vec3 m_Color{1.0};
    float m_Intensity{1.0};

  public:
    Light() = default;

    Light(glm::vec3 color, float intensity) : m_Color{color}, m_Intensity{intensity} {}
    virtual ~Light() = default;

    glm::vec3 getColor() const { return m_Color; }
    void setColor(glm::vec3 color) { m_Color = color; }

    float getIntensity() const { return m_Intensity; }
    void setIntensity(float intensity) { m_Intensity = intensity; }

    virtual glm::vec3 getPosition() const = 0;
    virtual void setPosition(glm::vec3 pos) = 0;

    /**
     * Gets a ray representing a light ray of this light source at a point in
     * world space
     *
     * @param worldPos The position in world space of the point on a object.
     * @return The Ray from this light source
     */
    virtual glm::vec3 getRay(const glm::vec3 worldPos) const = 0;
};
