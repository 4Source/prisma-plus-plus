#include "core/RayTracer.hpp"
#include "core/Ray.hpp"
#include <cmath>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

RayTracer::RayTracer(Scene s) : scene(s) { std::vector<std::vector<glm::vec3>> view{}; }

void RayTracer::start() {
    // initialize view

    int pixels_v = std::floor(scene.getCamera()->height() / scene.getCamera()->getResolution());
    int pixels_h = std::floor(scene.getCamera()->width() / scene.getCamera()->getResolution());

    for (int i = 0; i < pixels_v; i++) {
        view.emplace_back();
        for (int j = 0; j < pixels_h; j++) {
            view.at(i).emplace_back(255, 0, 255);
        }
    }

    // trace rays

    glm::vec3 top_left = scene.getCamera()->getPos() + scene.getCamera()->normal() * DISTANCE - 0.5f * scene.getCamera()->getTop() -
                         0.5f * scene.getCamera()->getLeft();
    glm::vec3 top_norm = glm::normalize(scene.getCamera()->getTop());
    glm::vec3 left_norm = glm::normalize(scene.getCamera()->getLeft());

    for (int i = 0; i < pixels_v; i++) {
        for (int j = 0; j < pixels_h; j++) {
            glm::vec3 point =
                top_left + float(i) * scene.getCamera()->getResolution() * left_norm + float(j) * scene.getCamera()->getResolution() * top_norm;
            glm::vec3 eye_to_point = point - scene.getCamera()->getPos();
            Subray s{eye_to_point, scene.getCamera()->getPos(), glm::vec3{255, 255, 255}, glm::vec3{0, 0, 0}};
            Ray r{s, scene.getObject(0), scene.getLight(0)}; // later whole object array
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
