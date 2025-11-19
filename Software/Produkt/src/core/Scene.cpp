#include "core/Scene.hpp"
#include <fstream>

Scene::Scene(const std::filesystem::path &scenePath) : m_Objects{}, m_Lights{} {
    std::ifstream file(scenePath);
    nlohmann::json data = nlohmann::json::parse(file);
}
void Scene::addObject(const std::shared_ptr<Object> &object) { m_Objects.push_back(object); }

std::shared_ptr<Object> Scene::getObject(uuids::uuid uuid) {
    for (auto &obj : m_Objects) {
        if (obj->getUUID() == uuid) {
            return obj;
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
    for (auto &light : m_Lights) {
        if (light->getUUID() == uuid) {
            return light;
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
    // 1. Handle Objects: Manually dereference pointers
    nlohmann::json objects_array = nlohmann::json::array();
    for (const auto &obj_ptr : scene.m_Objects) {
        if (obj_ptr) {
            // *obj_ptr triggers the to_json(json&, const Object&) function
            objects_array.push_back(*obj_ptr);
        }
    }

    // 2. Handle Lights: Manually dereference pointers
    nlohmann::json lights_array = nlohmann::json::array();
    for (const auto &light_ptr : scene.m_Lights) {
        if (light_ptr) {
            lights_array.push_back(*light_ptr);
        }
    }

    // 3. Handle Camera: Check for null and dereference
    nlohmann::json camera_json = nullptr;
    if (scene.m_Camera) {
        camera_json = *scene.m_Camera;
    }

    // 4. Helper for background color (assuming m_BackgroundColor exists in Scene)
    // If 'background' was a local variable in your code, replace usage below.
    // Here I assume it is a member variable named m_BackgroundColor.
    nlohmann::json bg_color = {
        {"r", 1.0}, {"g", 1.0}, {"b", 1.0} // Default
    };

    // Uncomment and adjust if you have this member:
    // bg_color = {{"r", scene.m_BackgroundColor.r}, {"g", scene.m_BackgroundColor.g}, {"b", scene.m_BackgroundColor.b}};

    // 5. Final Assembly
    j = nlohmann::json{
        {"scene_name", scene.m_Name}, {"objects", objects_array}, {"lights", lights_array}, {"camera", camera_json}, {"background_color", bg_color}};
}

void from_json(const nlohmann::json &j, Scene &scene) {
    j.at("name").get_to(scene.m_Name);
    j.at("objects").get_to(scene.m_Objects);
    j.at("lights").get_to(scene.m_Lights);
    j.at("camera").get_to(scene.m_Camera);

    nlohmann::json j_background = j.at("background_color");
    glm::vec3 background{1.0};
    background.x = j_background.at("x").get<float>();
    background.y = j_background.at("y").get<float>();
    background.z = j_background.at("z").get<float>();
}
