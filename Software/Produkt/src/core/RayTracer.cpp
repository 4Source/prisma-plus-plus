#include "core/RayTracer.hpp"
#include "core/Ray.hpp"
#include <cmath>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

RayTracer::RayTracer(Scene s) : scene(std::move(s)) { std::vector<std::vector<glm::vec3>> view{}; }

void RayTracer::start() {
    // initialize view

    int pixels_v = std::floor(scene.camera.height() / scene.camera.resolution);
    int pixels_h = std::floor(scene.camera.width() / scene.camera.resolution);

    for (int i = 0; i < pixels_v; i++) {
        view.emplace_back();
        for (int j = 0; j < pixels_h; j++) {
            view.at(i).emplace_back(255, 0, 255);
        }
    }

    // trace rays

    glm::vec3 top_left = scene.camera.pos + scene.camera.normal() * DISTANCE - 0.5f * scene.camera.top - 0.5f * scene.camera.left;
    glm::vec3 top_norm = glm::normalize(scene.camera.top);
    glm::vec3 left_norm = glm::normalize(scene.camera.left);

    for (int i = 0; i < pixels_v; i++) {
        for (int j = 0; j < pixels_h; j++) {
            glm::vec3 point = top_left + float(i) * scene.camera.resolution * left_norm + float(j) * scene.camera.resolution * top_norm;
            glm::vec3 eye_to_point = point - scene.camera.pos;
            Subray s{eye_to_point, scene.camera.pos, glm::vec3{255, 255, 255}, glm::vec3{0, 0, 0}};
            Ray r{s, scene.objects.at(0), scene.light}; // later whole object array
            view.at(i).at(j) = r.backward();
        }
    }
}

std::vector<std::vector<std::array<uint8_t, 3>>> RayTracer::view_to_rgb() {
    std::vector<std::vector<std::array<uint8_t, 3>>> rgb;
    for (int i = 0; i < view.size(); i++) {
        rgb.emplace_back();
        for (int j = 0; j < view.at(i).size(); j++) {
            uint8_t r = static_cast<uint8_t>(view.at(i).at(j).x);
            uint8_t g = static_cast<uint8_t>(view.at(i).at(j).y);
            uint8_t b = static_cast<uint8_t>(view.at(i).at(j).z);
            rgb.at(i).emplace_back(std::array<uint8_t, 3>{r, g, b});
        }
    }
    return rgb;
}
