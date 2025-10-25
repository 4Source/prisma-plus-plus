#pragma once

#include <glm/glm.hpp>

#include "core/Light.hpp"

class PointLight : public Light {
protected:
  glm::vec3 m_Pos{0};

public:
  PointLight();

  PointLight(glm::vec3 pos, glm::vec3 color, float intensity);

  glm::vec3 GetPosition() const { return m_Pos; }
  void SetPosition(glm::vec3 pos) { m_Pos = pos; }

  /**
   * Gets a ray representing a light ray of this light source at a point in
   * world space
   *
   * @param worldPos The position in world space of the point on a object.
   * @return The Ray from this light source which comes from light position
   * and goes to worldPos
   */
  virtual Ray GetRay(const glm::vec3 worldPos) const override;
};