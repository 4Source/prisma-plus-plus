#include "core/PointLight.hpp"

PointLight::PointLight() : Light{} {}

PointLight::PointLight(glm::vec3 pos, glm::vec3 color, float intensity) : m_Pos{pos}, Light{color, intensity} {}

glm::vec3 PointLight::getRay(const glm::vec3 worldPos) const { return worldPos - this->m_Pos; }
