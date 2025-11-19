#include "core/RayTracingRunner.hpp"
#include "core/HitComponentList.hpp"
#include "core/PerspectiveCamera.hpp"
#include "core/PointLight.hpp"
#include "core/RayTracer.hpp"
#include "core/Triangle.hpp"
#include <iostream>

Vertex v0{glm::vec3{-3, -3, 0}, glm::vec3{0.0f, 0.0f, -1.0f}};
Vertex v1{glm::vec3{5, 7, 0}, glm::vec3{0.0f, 0.0f, -1.0f}};
Vertex v2{glm::vec3{3, -3, 0}, glm::vec3{0.0f, 0.0f, -1.0f}};
Vertex v3{glm::vec3{-3, -3, 0}, glm::vec3{-0.26f, 0.2f, 0.94f}};
Vertex v4{glm::vec3{5, 7, 0}, glm::vec3{-0.26f, 0.2f, 0.94f}};
Vertex v5{glm::vec3{-4, 5, -2}, glm::vec3{-0.26f, 0.2f, 0.94f}};
Vertex v6{glm::vec3{-4, 5, -2}, glm::vec3{-0.28f, 0.36f, 0.89f}};
Vertex v7{glm::vec3{5, 7, 0}, glm::vec3{-0.28f, 0.36f, 0.89f}};
Vertex v8{glm::vec3{-2, 9, -3}, glm::vec3{-0.28f, 0.36f, 0.89f}};
Vertex v9{glm::vec3{5, 7, 0}, glm::vec3{0.54f, -0.62f, 0.57f}};
Vertex v10{glm::vec3{3, -3, 0}, glm::vec3{0.54f, -0.62f, 0.57f}};
Vertex v11{glm::vec3{12, 4, -1}, glm::vec3{0.54f, -0.62f, 0.57f}};
Vertex v12{glm::vec3{-3, -3, 0}, glm::vec3{0.0f, -0.08f, 1.0f}};
Vertex v13{glm::vec3{0, -9, -0.5}, glm::vec3{0.0f, -0.08f, 1.0f}};
Vertex v14{glm::vec3{3, -3, 0}, glm::vec3{0.0f, -0.08f, 1.0f}};

Scene createTestingScene() {

    std::shared_ptr<Triangle> tri1_p = std::make_shared<Triangle>(&v0, &v1, &v2);
    std::shared_ptr<Triangle> tri2_p = std::make_shared<Triangle>(&v3, &v4, &v5);
    std::shared_ptr<Triangle> tri3_p = std::make_shared<Triangle>(&v6, &v7, &v8);
    std::shared_ptr<Triangle> tri4_p = std::make_shared<Triangle>(&v9, &v10, &v11);
    std::shared_ptr<Triangle> tri5_p = std::make_shared<Triangle>(&v12, &v13, &v14);

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
        std::make_shared<PerspectiveCamera>(glm::vec3{0, -0.1, 10}, glm::vec3{0, 12.8, 0}, glm::vec3{9.6, 0, 0}, 0.01);
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(glm::vec3{0, 5, 5}, glm::vec3{255, 255, 255}, 1.0);

    Scene scene{light, std::vector<std::shared_ptr<Object>>{object_p}, camera};
    return scene;
}

std::unique_ptr<RunnerResult> RayTracingRunner::run() {
    auto result = std::make_unique<RunnerResult>();
    std::shared_ptr<PerspectiveCamera> camera =
        std::make_shared<PerspectiveCamera>(glm::vec3{0, -0.1, 10}, glm::vec3{0, 12.8, 0}, glm::vec3{9.6, 0, 0}, 0.01);
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
