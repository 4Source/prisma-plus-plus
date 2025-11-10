#include "core/Scene.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

Scene::Scene(const std::filesystem::path &scenePath) : m_Objects{}, m_Lights{} {
    std::ifstream file(scenePath);
    nlohmann::json data = nlohmann::json::parse(file);

    int i;
}
void Scene::exportScene(const std::filesystem::path &scenePath) { std::ifstream file(scenePath); }