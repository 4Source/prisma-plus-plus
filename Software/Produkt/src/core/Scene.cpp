#include "core/Scene.hpp"
#include <fstream>

Scene::Scene(const std::filesystem::path &scenePath) : m_Objects{}, m_Lights{} {
    std::ifstream file(scenePath);
    nlohmann::json data = nlohmann::json::parse(file);

    int i;
}
void Scene::exportScene(const std::filesystem::path &scenePath) { std::ifstream file(scenePath); }

void to_json(nlohmann::json &j, const Scene &scene) {
    // TODO: Scene to json
    j = nlohmann::json{{"objects", 1}};
}

void from_json(const nlohmann::json &j, Scene &scene) {
    // TODO: Scene from json
}
