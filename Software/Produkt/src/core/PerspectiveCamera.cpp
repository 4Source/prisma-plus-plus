 #include "core/PerspectiveCamera.hpp"
 #include "core/glm_json.hpp"

void to_json(nlohmann::json &j, const PerspectiveCamera &camera){};
void from_json(const nlohmann::json &j, PerspectiveCamera &camera){};