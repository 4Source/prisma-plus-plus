#pragma once
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace glm {
inline void to_json(nlohmann::json &j, const vec3 &vec) { j = nlohmann::json{{"x", vec.x}, {"y", vec.y}, {"z", vec.z}}; }

inline void from_json(const nlohmann::json &j, vec3 &vec) {
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
    j.at("z").get_to(vec.z);
}
} // namespace glm
