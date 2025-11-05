#include "cli/CliManager.h"
#include "cli/CliArguments.h"
#include <iostream>
#include "ui/UIManager.h"
#include <fstream>
#include <sstream>

bool CliManager::loadFromFile(const std::string &path, tinyobj::attrib_t &attributes, std::vector<tinyobj::shape_t> &shapes, std::string &error) {
    std::ifstream file(path);
    if (!file) {
        return false;
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string data = ss.str();
    
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig config;
    config.triangulate = true;

    if (!reader.ParseFromString(data, "", config)) {
        std::cout << "OBJ parse error: " << reader.Error() << "\n";
        return false;
    }

    attributes = reader.GetAttrib();
    shapes = reader.GetShapes();

    return true;
}

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
    //TODO: write cli output to standard output

bool CliManager::stdinHasData() {
    return !isatty(fileno(stdin));
}
/// @brief Main program startup controller
/// @param args 
/// @return error code - 1 - general run error , 2 - parser error, 3 - help request
//How can errors be handled - for top level with error codes??
int CliManager::run(std::span<const char* const> args) {
    auto CliArgs = CliArguments::parse(args);
    if (CliArgs.helpRequested)
        return 3;
    
    if (CliManager::stdinHasData()) {
        //Standard input recognized -> use file from stdin
        std::cout << "STDIN data recognized, possible --file option is ignored!.\n";
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::string error;
        if (!CliManager::loadFromStdin(attrib, shapes, error)) {
            std::cerr << "Parse error: " << error << "\n";
            return 2;
        }
        std::cout << "Loaded OBJ: " << shapes.size() << " shapes, " << attrib.vertices.size() / 3 << " vertices\n";
        return 0;
    }
    if(CliArgs.valid){
        //Run with file parser from --file option
        std::cout << "File recognized" << "\n";
        std::cout << "Path:\n" << CliArgs.file << "\n";
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::string error;
        if (!CliManager::loadFromFile(CliArgs.file, attrib, shapes, error)) {
            std::cerr << "Parse error: " << error << "\n";
            return 2;
        }
        std::cout << "Loaded OBJ: " << shapes.size() << " shapes, " << attrib.vertices.size() / 3 << " vertices\n";
        return 0;
    }
    if(!CliArgs.valid){
        std::cout << "No valid CLI Arguments - Starting UI" << "\n";
        UIManager ui(800, 600, "Prisma++"); // NOLINT
        ui.run();                           // run main UI loop
        return 0;
    }
    return 1;
}