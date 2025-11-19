#include "core/PointLight.hpp"

PointLight::PointLight() : Light{} {}

PointLight::PointLight(glm::vec3 pos, glm::vec3 color, float intensity) : m_Pos{pos}, Light{color, intensity} {}

glm::vec3 PointLight::getRay(const glm::vec3 worldPos) const { return worldPos - this->m_Pos; }

void to_json(nlohmann::json &j, const PointLight &light) {
    glm::vec3 position = light.getPosition();
    glm::vec3 rotation = light.getRotation();
    glm::vec3 color = light.getColor();

    j = nlohmann::json{{"name", light.getName()},
                       {"type", "point"},
                       {"luminosity", light.getIntensity()},
                       {"position", {{"x", position.x}, {"y", position.y}, {"z", position.z}}},
                       {"rotation", {{"x", rotation.x}, {"y", rotation.y}, {"z", rotation.z}}},
                       {"color", {{"r", color.r}, {"g", color.g}, {"b", color.b}}}};
}

void from_json(const nlohmann::json &j, PointLight &light) {
    light.setName(j.at("name").get<std::string>());
    light.setIntensity(j.at("luminosity").get<float>());

    nlohmann::json j_pos = j.at("position");
    glm::vec3 v_pos{1.0};
    v_pos.x = j_pos.at("x").get<float>();
    v_pos.y = j_pos.at("y").get<float>();
    v_pos.z = j_pos.at("z").get<float>();
    light.setPosition(v_pos);

    nlohmann::json j_rotation = j.at("rotation");
    glm::vec3 v_rotation{1.0};
    v_rotation.x = j_rotation.at("x").get<float>();
    v_rotation.y = j_rotation.at("y").get<float>();
    v_rotation.z = j_rotation.at("z").get<float>();
    light.setRotation(v_rotation);

    nlohmann::json j_color = j.at("color");
    glm::vec3 v_color{1.0};
    v_color.r = j_color.at("r").get<float>();
    v_color.g = j_color.at("g").get<float>();
    v_color.b = j_color.at("b").get<float>();
    light.setColor(v_color);
}
