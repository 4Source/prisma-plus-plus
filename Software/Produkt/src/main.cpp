#include "ui/UIManager.h"
#include <firstcode.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "tiny_obj_loader.h"
#include <cxxopts.hpp> // Otionpareser nutzen ??
#include <unistd.h>

bool stdinHasData() { return !isatty(fileno(stdin)); }

int createUI() {
    //  create window
    std::cout << "Create MainWindow" << "\n";
    UIManager ui(800, 600, "Prisma++");
    ui.run(); // run main UI loop
    return 0;
}

int parseStandardInput(tinyobj::attrib_t &attributes, std::vector<tinyobj::shape_t> &shapes) {
    std::stringstream buffer;
    buffer << std::cin.rdbuf();
    std::string objData = buffer.str();

    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig config;
    config.triangulate = true;

    if (!reader.ParseFromString(objData, "", config)) {
        std::cout << "OBJ parse error: " << reader.Error() << "\n";
        return 2;
    }

    attributes = reader.GetAttrib();
    shapes = reader.GetShapes();

    return 0;
}

int runCLI(int argc, const char *argv[]) {

    cxxopts::Options options("Application name", "Application description");

    options.add_options()
        ("h,help", "show help")
        ("f,file", "file name", cxxopts::value<std::string>())
        ("v,verbose", "verbose output", cxxopts::value<bool>()->default_value("false"))
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << "\n";
        return EXIT_FAILURE;
    }

    if (result.count("file") < 1)
    {
        std::cout << options.help() << "\n";
        return EXIT_FAILURE;
    }

    std::string fileName = result["file"].as<std::string>();

    std::cout << "Starting CLI\n";
    if (!stdinHasData()) {
        std::cout << "Program startet without input!" << "\n";
        return 0;
    }
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;

    //TODO: Errorhandling of parserStandardInp
    if (parseStandardInput(attributes, shapes) != 0) {
        return 1;
    } else {
        std::cout << "Loaded OBJ with " << shapes.size() << " shapes and " << attributes.vertices.size() / 3 << " vertices\n";
    }
    return 0;
}

int main(int argc, const char *argv[]) { // NOLINT(bugprone-exception-escape)
    try {
        std::cout << "Hello Prisma++" << "\n";
        std::cout << "Add-Lib: " << add(1, 2) << "\n";

        return runCLI(argc, argv);
    } catch (const std::exception &e) {
        // Handle it internally to prevent it from escaping.
        // Note: I/O itself can still throw, but this is the intent.
        std::cerr << "ERROR: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "ERROR: Unknown exception caught." << "\n";
    }

    // Since we caught the exception, we can still exit cleanly with an error code.
    return 1;
}

int test() { return 1; }
