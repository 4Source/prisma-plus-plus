#pragma once

#include "core/Light.hpp"
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

class PointLight : public Light {
  protected:
    glm::vec3 m_Pos{0};
    glm::vec3 m_Rotation{0};
    std::string m_Type{"point"};

  public:
    PointLight();

    PointLight(glm::vec3 pos, glm::vec3 color, float intensity);

    glm::vec3 getPosition() const override { return m_Pos; }
    void setPosition(glm::vec3 pos) override { m_Pos = pos; }

    glm::vec3 getRotation() const { return m_Rotation; }
    void setRotation(glm::vec3 rot) { m_Rotation = rot; }

    /**
     * Gets a ray representing a light ray of this light source at a point in
     * world space
     *
     * @param worldPos The position in world space of the point on a object.
     * @return The Ray from this light source which comes from light position
     * and goes to worldPos
     */
    virtual glm::vec3 getRay(const glm::vec3 worldPos) const override;

    friend void to_json(nlohmann::json &j, const PointLight &light);
    friend void from_json(const nlohmann::json &j, const PointLight &light);
};
