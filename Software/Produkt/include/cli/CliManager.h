#pragma once

#include <vector>
#include <string>
#include "tiny_obj_loader.h"
#include <cxxopts.hpp>
#include <unistd.h>
#include <span>

struct CliArguments;

class CliManager {
public:
    static bool loadFromFile(const std::string& path,
                               tinyobj::attrib_t& attributes,
                               std::vector<tinyobj::shape_t>& shapes,
                               std::string& error);

    static bool loadFromStdin(tinyobj::attrib_t& attributes,
                              std::vector<tinyobj::shape_t>& shapes,
                              std::string& error);

    static bool stdinHasData();

    static int run(std::span<const char* const> args);

    //TODO: write cli output to standard output
};