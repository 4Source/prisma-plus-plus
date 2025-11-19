#include "core/Scene.hpp"
#include <core/PerspectiveCamera.hpp>
#include <core/PointLight.hpp>
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

/*
 * Converts a Scene object into a JSON representation.
 */
void to_json(nlohmann::json &j, const Scene &scene) {
    // Prepare Arrays for Objects and Lights
    nlohmann::json objects_array = nlohmann::json::array();
    nlohmann::json lights_array = nlohmann::json::array();

    // Iterate and Dereference Objects
    for (const std::shared_ptr<Object> &obj_ptr : scene.m_Objects) {
        if (obj_ptr) {
            objects_array.push_back(*obj_ptr);
        }
    }

    // Iterate and Dereference Lights, while checking for Light type
    for (const std::shared_ptr<Light> &light_ptr : scene.m_Lights) {
        std::shared_ptr<PointLight> pl = std::dynamic_pointer_cast<PointLight>(light_ptr);
        if (pl) {
            lights_array.push_back(*pl);
        }
    }

    // Check for Camera Type
    nlohmann::json j_camera;
    std::shared_ptr<PerspectiveCamera> pc = std::dynamic_pointer_cast<PerspectiveCamera>(scene.m_Camera);
    if (pc) {
        j_camera = *pc;
    }

    // Construct the Main Scene Object
    j = nlohmann::json{{"scene_name", scene.m_Name},
                       {"objects", objects_array},
                       {"lights", lights_array},
                       {"camera", j_camera},
                       // Manual construction for background color (r, g, b)
                       // Assuming m_BackgroundColor is a glm::vec3
                       {"background_color", {{"r", scene.m_BackgroundColor.r}, {"g", scene.m_BackgroundColor.g}, {"b", scene.m_BackgroundColor.b}}}};
}

/*
 * Crafts a Scene object from a JSON representation.
 */
void from_json(const nlohmann::json &j, Scene &scene) {
    // Scene name
    j.at("scene_name").get_to(scene.m_Name);

    // Background color
    const nlohmann::json &j_bg = j.at("background_color");
    scene.m_BackgroundColor = glm::vec3(j_bg.at("r").get<float>(), j_bg.at("g").get<float>(), j_bg.at("b").get<float>());

    // Camera(always PerspectiveCamera)
    scene.m_Camera = std::make_shared<PerspectiveCamera>();
    j.at("camera").get_to(*std::static_pointer_cast<PerspectiveCamera>(scene.m_Camera));

    // Objects (always teh same type)
    scene.m_Objects.clear();
    for (const nlohmann::json &jobj : j.at("objects")) {
        std::shared_ptr<Object> obj = std::make_shared<Object>();
        jobj.get_to(*obj);
        scene.m_Objects.push_back(obj);
    }

    // Lights (Uses the "type" attribute in the JSON)
    scene.m_Lights.clear();
    for (const nlohmann::json &j_light : j.at("lights")) {
        std::string type = j_light.at("type").get<std::string>();

        if (type == "point") {
            std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
            j_light.get_to(*light);
            scene.m_Lights.push_back(light);
        } else {
            throw std::runtime_error("Unknown light type: " + type);
        }
    }
}
