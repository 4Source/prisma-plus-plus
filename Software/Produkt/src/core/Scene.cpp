#include "core/Scene.hpp"
#include <fstream>

Scene::Scene(const std::filesystem::path &scenePath) : m_Objects{}, m_Lights{} {
    std::ifstream file(scenePath);
    nlohmann::json data = nlohmann::json::parse(file);
}
void Scene::addObject(const std::shared_ptr<Object> &object) { m_Objects.push_back(object); }

std::shared_ptr<Object> Scene::getObject(uuids::uuid uuid) {
    for (size_t i = 0; i < m_Objects.size(); i++) {
        if (m_Objects.at(i)->getUUID() == uuid) {
            return m_Objects.at(i);
        }
    }
    return nullptr;
}

void Scene::removeObject(uuids::uuid uuid) {
    auto to_remove = std::remove_if(m_Objects.begin(), m_Objects.end(), [&](const std::shared_ptr<Object> &c) { return c->getUUID() == uuid; });
    m_Objects.erase(to_remove, m_Objects.end());
}

void Scene::addLight(const std::shared_ptr<Light> &light) { m_Lights.push_back(light); }

std::shared_ptr<Light> Scene::getLight(uuids::uuid uuid) {
    for (size_t i = 0; i < m_Lights.size(); i++) {
        if (m_Lights.at(i)->getUUID() == uuid) {
            return m_Lights.at(i);
        }
    }
    return nullptr;
}

void Scene::removeLight(uuids::uuid uuid) {
    auto to_remove = std::remove_if(m_Lights.begin(), m_Lights.end(), [&](const std::shared_ptr<Light> &c) { return c->getUUID() == uuid; });
    m_Lights.erase(to_remove, m_Lights.end());
}

void Scene::exportScene(const std::filesystem::path &scenePath) {
    // TODO: Export Scene to file
    std::ifstream file(scenePath);
}

void to_json(nlohmann::json &j, const Scene &scene) {
    // TODO: Scene to json
}

void from_json(const nlohmann::json &j, Scene &scene) {
    // TODO: Scene from json
}
