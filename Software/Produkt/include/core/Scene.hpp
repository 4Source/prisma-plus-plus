#pragma once
#include "core/Camera.hpp"
#include "core/Light.hpp"
#include "core/Object.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

class Scene {
  private:
    std::vector<std::shared_ptr<Object>> m_Objects;
    std::shared_ptr<Camera> m_Camera;
    std::vector<std::shared_ptr<Light>> m_Lights;

  public:
    Scene(std::shared_ptr<Light> light, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<Camera> camera)
        : m_Lights{light}, m_Objects{objects}, m_Camera{camera} {}
    Scene(const std::filesystem::path &scenePath);
    ~Scene() = default;

    std::vector<std::shared_ptr<Object>> getObjects() { return m_Objects; }
    std::shared_ptr<Object> getObject(size_t index) { return m_Objects.at(index); }
    std::shared_ptr<Camera> getCamera() { return m_Camera; }
    std::vector<std::shared_ptr<Light>> getLights() { return m_Lights; }
    std::shared_ptr<Light> getLight(size_t index) { return m_Lights.at(index); }

    // Scene(const Scene &) = delete;
    // Scene &operator=(const Scene &) = delete;

    // Scene(Scene &&) noexcept = delete;
    // Scene &operator=(Scene &&) noexcept = delete;

    void exportScene(const std::filesystem::path &scenePath);
    friend void to_json(nlohmann::json &j, const Scene &scene);
    friend void from_json(const nlohmann::json &j, const Scene &scene);
};