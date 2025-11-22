#pragma once
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

class Color : public glm::vec3 {
  public:
    using glm::vec3::vec3;

    template <typename V> Color(const V &v) : glm::vec3(v) {}
};

inline void to_json(nlohmann::json &j, const Color &color) { j = nlohmann::json{{"r", color.r}, {"g", color.g}, {"b", color.b}}; }

inline void from_json(const nlohmann::json &j, Color &color) {
    j.at("r").get_to(color.r);
    j.at("g").get_to(color.g);
    j.at("b").get_to(color.b);
}
