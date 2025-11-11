#include "cli/CliManager.h"
#include "cli/CliArguments.h"
#include "ui/UIManager.h"
#include "core/RayTracingRunner.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "stb_image_write.h"
#pragma GCC diagnostic pop

#include <array>
#include <string>
#include <vector>
#include "core/Object.hpp"

bool CliManager::save_png(const std::vector<std::vector<std::array<uint8_t, 3>>> &img, const std::string &filename) {
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
bool CliManager::writeOutputFile(const std::filesystem::path &path, const std::vector<std::vector<std::array<uint8_t, 3>>> &data, const int height,
                                 const int width) {
    std::ofstream file(path, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open default file!\n";
        return false;
    }

    // Write image data here
    // file << "Write Image here...\n";
    return save_png(data, path.string());
    // file.close();
    // return true;
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
        
        // TODO: outsource to RayTracingRunner
        //  basic raytracing algorithm example
        // Generate object from file
        auto obj = std::make_shared<Object>(attrib, shapes);

        // print Object
        std::cout << obj->toString() << "\n";
        RayTracingRunner runner(obj);
        auto picture_ptr = runner.run();
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
        // TODO: pass raytracer output to method
        // Better give picture_ptr to writeOutputFile
        return CliManager::writeOutputFile(output_path, (*picture_ptr).img, (*picture_ptr).height, (*picture_ptr).width);
    }

    // If no Standard input is passed run UI
    std::cout << "No valid CLI Arguments - Starting UI" << "\n";
    UIManager ui(800, 600, "Prisma++"); // NOLINT
    ui.run();                           // run main UI loop
    return 0;
}
