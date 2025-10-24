#pragma once

#include <glm/glm.hpp>

// TODO: Remove this is temporary declaration
using Ray = glm::vec3;

class Light {
protected:
  glm::vec3 m_Color{1.0};
  float m_Intensity{1.0};

public:
  Light() = default;

  Light(glm::vec3 color, float intensity)
      : m_Color{color}, m_Intensity{intensity} {}
  virtual ~Light() = default;

  /**
   * Gets a ray representing a light ray of this light source at a point in
   * world space
   *
   * @param worldPos The position in world space of the point on a object.
   * @return The Ray from this light source
   */
  virtual Ray GetRay(const glm::vec3 worldPos) const = 0;

  /**
   * Returns the Color of the light.
   * @return The Color
   */
  virtual glm::vec3 GetColor() { return m_Color; }

  /**
   * Returns the Intensity of the light.
   * @return The intensity
   */
  virtual float GetIntensity() { return m_Intensity; }
};