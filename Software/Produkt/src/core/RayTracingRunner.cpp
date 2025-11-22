#include "core/RayTracingRunner.hpp"
#include "core/HitComponentList.hpp"
#include "core/PerspectiveCamera.hpp"
#include "core/PointLight.hpp"
#include "core/RayTracer.hpp"
#include "core/Triangle.hpp"
#include <iostream>

Scene createTestingScene() {

    std::shared_ptr<Triangle> tri1_p = std::make_shared<Triangle>(glm::vec3{-3, -3, 0}, glm::vec3{5, 7, 0}, glm::vec3{3, -3, 0});
    std::shared_ptr<Triangle> tri2_p = std::make_shared<Triangle>(glm::vec3{-3, -3, 0}, glm::vec3{5, 7, 0}, glm::vec3{-4, 5, -2});
    std::shared_ptr<Triangle> tri3_p = std::make_shared<Triangle>(glm::vec3{-4, 5, -2}, glm::vec3{5, 7, 0}, glm::vec3{-2, 9, -3});
    std::shared_ptr<Triangle> tri4_p = std::make_shared<Triangle>(glm::vec3{5, 7, 0}, glm::vec3{3, -3, 0}, glm::vec3{12, 4, -1});
    std::shared_ptr<Triangle> tri5_p = std::make_shared<Triangle>(glm::vec3{-3, -3, 0}, glm::vec3{0, -9, -0.5}, glm::vec3{3, -3, 0});

    std::shared_ptr<HitComponentList> list = std::make_shared<HitComponentList>();
    list->add(tri1_p);
    list->add(tri2_p);
    list->add(tri3_p);
    list->add(tri4_p);
    list->add(tri5_p);

    Material material{glm::vec3{0, 255, 255}};
    std::shared_ptr<Material> material_p = std::make_shared<Material>(material);
    std::shared_ptr<Object> object_p = std::make_shared<Object>(list, material_p);

    std::shared_ptr<PerspectiveCamera> camera =
        std::make_shared<PerspectiveCamera>(glm::vec3{0, -0.1, 10}, glm::vec3{1, 0, 0}, glm::vec3{-1, 0, 0}, 5.0, 12.8, 960, 1280);
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(glm::vec3{0, 5, 5}, glm::vec3{255, 255, 255}, 1.0);

    Scene scene{light, std::vector<std::shared_ptr<Object>>{object_p}, camera};
    return scene;
}

std::unique_ptr<RunnerResult> RayTracingRunner::run() {
    auto result = std::make_unique<RunnerResult>();
    std::shared_ptr<PerspectiveCamera> camera =
        std::make_shared<PerspectiveCamera>(glm::vec3{5, 5, 5}, glm::vec3{-1, 1, 0}, glm::vec3{-1, -1, -1}, 1.0, 12.8, 1280, 960);
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(glm::vec3{0, 5, 5}, glm::vec3{255, 255, 255}, 1.0);

    // TODO: making sharedpntr later give sharedpntr to Constructor
    // If no scene is given create a default scene
    Scene scene = (obj_ptr_ == nullptr) ? createTestingScene() : Scene{light, std::vector<std::shared_ptr<Object>>{obj_ptr_}, camera};

    RayTracer raytracer{scene};
    raytracer.start();

    result->height = 960;
    result->width = 1280;
    result->img = raytracer.view_to_rgb();
    return result;
}
