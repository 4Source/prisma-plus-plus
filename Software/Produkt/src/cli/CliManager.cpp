#include "CliManager.h"
#include "CliArguments.h"
#include <iostream>

bool loadFromString(const std::string &data, tinyobj::attrib_t &attributes, std::vector<tinyobj::shape_t> &shapes, std::string &error) {

}

bool loadFromStdin(tinyobj::attrib_t &attributes, std::vector<tinyobj::shape_t> &shapes, std::string &error) {
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

bool stdinHasData() {
    return !isatty(fileno(stdin));
}

int CliManager::run(int argc, const char *argv[]) {
    auto args = CliArguments::parse(argc, argv);
    if (args.helpRequested || !args.valid)
        return 1;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::string error;

    if (!stdinHasData()) {
        std::cout << "No STDIN data, exiting.\n";
        return 0;
    }

    if (!loadFromStdin(attrib, shapes, error)) {
        std::cerr << "Parse error: " << error << "\n";
        return 2;
    }

    std::cout << "Loaded OBJ: " << shapes.size() << " shapes, " << attrib.vertices.size() / 3 << " vertices\n";

    return 0;
}