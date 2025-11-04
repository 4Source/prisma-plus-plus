#pragma once

#include <vector>
#include <string>
#include "tiny_obj_loader.h"
#include <cxxopts.hpp>
#include <unistd.h>
struct CliArguments;

class CliManager {
public:
    static bool loadFromString(const std::string& data,
                               tinyobj::attrib_t& attributes,
                               std::vector<tinyobj::shape_t>& shapes,
                               std::string& error);

    static bool loadFromStdin(tinyobj::attrib_t& attributes,
                              std::vector<tinyobj::shape_t>& shapes,
                              std::string& error);

    static bool stdinHasData();

    static int run(int argc, const char* argv[]);
};