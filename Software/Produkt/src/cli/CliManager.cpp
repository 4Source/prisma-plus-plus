#include "cli/CliManager.h"
#include "cli/CliArguments.h"
#include "ui/UIManager.h"

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
bool CliManager::writeOutputFile(const std::filesystem::path &path, std::vector<glm::vec3> &data, const int height, const int width) {
    std::ofstream file(path, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open default file!\n";
        return false;
    }

    // Write image data here
    file << "Write Image here...\n";

    file.close();
    return true;
}

/// @brief
/// @return standard input exist - true : flase
bool CliManager::stdinHasData() { return !isatty(fileno(stdin)); }

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

        //-------------------------------------------------------------------------------------------------------------
        //
        // run raytracing here
        //
        //-------------------------------------------------------------------------------------------------------------
        std::vector<glm::vec3> raytracing_data;
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

        if (CliManager::writeOutputFile(output_path, raytracing_data, 920, 1080))
            return 0;
        return 1;
    }

    // If no Standard input is passed run UI
    std::cout << "No valid CLI Arguments - Starting UI" << "\n";
    UIManager ui(800, 600, "Prisma++"); // NOLINT
    ui.run();                           // run main UI loop
    return 0;
}