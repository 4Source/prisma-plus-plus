#include "cli/CliManager.h"
#include "cli/CliArguments.h"
#include "ui/UIManager.h"
#include "core/RayTracer.hpp"
#include "core/Triangle.hpp"
#include "core/HitComponentList.hpp"
#include "core/PointLight.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "cli/stb_image_write.h"
#pragma GCC diagnostic pop

#include <vector>
#include <array>
#include <string>

bool CliManager::save_png(const std::vector<std::vector<std::array<uint8_t, 3>>>& img,
              const std::string& filename) {
    int height = static_cast<int>(img.size());
    int width = static_cast<int>(img[0].size());

    // Flatten the image data into a single contiguous buffer
    std::vector<uint8_t> data;
    data.reserve(static_cast<size_t>(width) * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            data.push_back(img[y][x][0]); // R
            data.push_back(img[y][x][1]); // G
            data.push_back(img[y][x][2]); // B
        }
    }

    // Write PNG (stride = width * 3 bytes)
    return stbi_write_png(filename.c_str(), width, height, 3, data.data(), width * 3);
}

/// @brief load .obj File from standard input and parse with tinyobjparser
/// @param attributes
/// @param shapes
/// @param error
/// @return
bool CliManager::loadFromStdin(tinyobj::attrib_t &attributes, std::vector<tinyobj::shape_t> &shapes, std::string &error) {
    std::stringstream buffer;
    buffer << std::cin.rdbuf();
    std::string objData = buffer.str();

    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig config;
    config.triangulate = true;

    if (!reader.ParseFromString(objData, "", config)) {
        std::cout << "OBJ parse error: " << reader.Error() << "\n";
        return false;
    }

    attributes = reader.GetAttrib();
    shapes = reader.GetShapes();

    return true;
}

/// @brief checks if path is given and writes to file or to default file
/// @param data
/// @param height
/// @param width
/// @return
bool CliManager::writeOutputFile(const std::filesystem::path &path, const std::vector<std::vector<std::array<uint8_t, 3>>> &data, const int height, const int width) {
    std::ofstream file(path, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open default file!\n";
        return false;
    }

    // Write image data here
    //file << "Write Image here...\n";
	return save_png(data, path.string()); 
    //file.close();
    //return true;
}

/// @brief
/// @return standard input exist - true : flase
bool CliManager::stdinHasData() { 
    #ifdef _WIN32
        return !_isatty(_fileno(stdin));
    #else
        return !isatty(fileno(stdin));
    #endif
}

/// @brief Main program startup controller
/// @param args
/// @return error code - 1 - general run error , 2 - parser error, 3 - help request
// How can errors be handled - for top level with error codes??
int CliManager::run(std::span<const char *const> args) {
    auto CliArgs = CliArguments::parse(args);
    if (CliArgs.helpRequested)
        return 3;

    if (CliManager::stdinHasData()) {
        // Standard input recognized -> use file from stdin
        std::cout << "STDIN data recognized.\n";
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::string error;
        if (!CliManager::loadFromStdin(attrib, shapes, error)) {
            std::cerr << "Parse error: " << error << "\n";
            return 2;
        }
        std::cout << "Loaded OBJ: " << shapes.size() << " shapes, " << attrib.vertices.size() / 3 << " vertices\n";

		//  basic raytracing algorithm example
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

        Camera camera{glm::vec3{0, -0.1, 10}, glm::vec3{0, 12.8, 0}, glm::vec3{9.6, 0, 0}, 0.01};
        PointLight light{glm::vec3{0, 5, 5}, glm::vec3{255, 255, 255}, 1.0};

        Scene scene{light, std::vector<std::shared_ptr<Object>>{object_p}, camera};
        RayTracer raytracer{scene};
        raytracer.start();

        std::filesystem::path output_path;

        if (!CliArgs.file.empty() && CliArgs.createFile)
            output_path = CliArgs.file;
        else
            output_path = "default/output.png";

        if (!output_path.parent_path().empty() && !std::filesystem::exists(output_path.parent_path()))
            std::filesystem::create_directories(output_path.parent_path());
        // Create the file
        std::ofstream file(output_path);
        if (!file) {
            std::cerr << "Failed to create file: " << output_path << "\n";
            return 1;
        }

        return CliManager::writeOutputFile(output_path, raytracer.view_to_rgb(), 960, 1280);
            
    }

    // If no Standard input is passed run UI
    std::cout << "No valid CLI Arguments - Starting UI" << "\n";
    UIManager ui(800, 600, "Prisma++"); // NOLINT
    ui.run();                           // run main UI loop
    return 0;
}
