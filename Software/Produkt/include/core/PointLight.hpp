#pragma once

#include "core/Light.hpp"
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

class PointLight : public Light {
  protected:
    glm::vec3 m_Pos{0};

  public:
    PointLight();

    PointLight(glm::vec3 pos, glm::vec3 color, float intensity);

    glm::vec3 getPosition() const override { return m_Pos; }
    void setPosition(glm::vec3 pos) override { m_Pos = pos; }

    virtual glm::vec3 getRay(const glm::vec3 worldPos) const override;

    friend void to_json(nlohmann::json &j, const PointLight &light);
    friend void from_json(const nlohmann::json &j, const PointLight &light);
};
