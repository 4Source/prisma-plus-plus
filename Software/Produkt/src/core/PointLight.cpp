#include "core/PointLight.hpp"
#include "core/glm_json.hpp"

PointLight::PointLight(glm::vec3 pos, glm::vec3 color, float intensity) : m_Pos{pos}, Light{color, intensity} {}

glm::vec3 PointLight::getRay(const glm::vec3 worldPos) const { return worldPos - this->m_Pos; }

/*
 * Converts a Scene object into a JSON representation.
 */
void to_json(nlohmann::json &j, const PointLight &light) {
    j = nlohmann::json{{"name", light.m_Name},    {"type", light.m_Type},         {"luminosity", light.m_Intensity},
                       {"position", light.m_Pos}, {"rotation", light.m_Rotation}, {"color", light.m_Color}};
}

/*
 * Crafts a Scene object from a JSON representation.
 */
void from_json(const nlohmann::json &j, PointLight &light) {
    light.setName(j.at("name").get<std::string>());
    light.setIntensity(j.at("luminosity").get<float>());
    light.setPosition(j.at("position").get<glm::vec3>());
    light.setPosition(j.at("rotation").get<glm::vec3>());
    light.setPosition(j.at("color").get<Color>());
}
