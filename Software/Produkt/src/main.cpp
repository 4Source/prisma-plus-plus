#include "cli/CliManager.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdint>
#include <optionparser.h>
#include "RayTracer.hpp"
#include "Triangle.hpp"
#include "ComponentList.hpp"


// from Ray Tracing in One Weekend to visualize output array

void save_ppm(const std::vector<std::vector<std::array<uint8_t, 3>>>& img,
              const std::string& filename) {
    int height = img.size();
    int width = img[0].size();

    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int y = 0; y < height; y++) { // flip vertically if needed
        for (int x = 0; x < width; ++x) {
            ofs.write(reinterpret_cast<const char*>(img[y][x].data()), 3);
        }
    }
}


/// @brief
/// @param argc
/// @param argv
/// @return
int main(int argc, char *argv[]) { // NOLINT
    try {
        std::cout << "Hello Prisma++" << "\n";
        std::cout << "Add-Lib: " << add(1, 2) << "\n";

        //  basic raytracing algorithm example
        Triangle tri1{{glm::vec3{-3, -3, 0}, glm::vec3{5, 7, 0}, glm::vec3{3, -3, 0}}};
        std::shared_ptr<Triangle> tri1_p = std::make_shared<Triangle>(tri1);
        Triangle tri2{{glm::vec3{-3, -3, 0}, glm::vec3{5, 7, 0}, glm::vec3{-4, 5, -2}}};
        std::shared_ptr<Triangle> tri2_p = std::make_shared<Triangle>(tri2);
        Triangle tri3{{glm::vec3{-4, 5, -2}, glm::vec3{5, 7, 0}, glm::vec3{-2, 9, -3}}};
        std::shared_ptr<Triangle> tri3_p = std::make_shared<Triangle>(tri3);
        Triangle tri4{{glm::vec3{5, 7, 0}, glm::vec3{3, -3, 0}, glm::vec3{12, 4, -1}}};
        std::shared_ptr<Triangle> tri4_p = std::make_shared<Triangle>(tri4);
        Triangle tri5{{glm::vec3{-3, -3, 0}, glm::vec3{0, -9, -0.5}, glm::vec3{3, -3, 0}}};
        std::shared_ptr<Triangle> tri5_p = std::make_shared<Triangle>(tri5);

        ComponentList list{};
        list.add(tri1_p);
        list.add(tri2_p);
        list.add(tri3_p);
        list.add(tri4_p);
        list.add(tri5_p);

        std::shared_ptr<ComponentList> list_p = std::make_shared<ComponentList>(list);
        Object object{list_p, Material{glm::vec3{0, 255, 255}}};

        Camera camera{glm::vec3{0, -0.1, 10}, glm::vec3{0, 12.8, 0}, glm::vec3{9.6, 0, 0}, 0.01};
        Light light{glm::vec3{255, 255, 255}, 1.0, glm::vec3{0, 5, 5}};

        Scene scene{light, std::vector<Object>{object}, camera};
        RayTracer raytracer{scene};
        raytracer.start();

        save_ppm(raytracer.view_to_rgb(), "output.ppm"); //visualize output array

        //  create window
        UIManager ui(800, 600, "Prisma++");
        ui.run(); // run main UI loop
        return 0;
    //master:   return CliManager::run({argv, static_cast<size_t>(argc)});
    } catch (const std::exception &e) {
        std::cerr << "FATAL: " << e.what() << "\n";
    }
    return 1;
}

auto test() -> int
{
    return 1;
}
