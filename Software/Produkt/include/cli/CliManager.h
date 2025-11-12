#pragma once

#include "tiny_obj_loader.h"
#include <cxxopts.hpp>
#include <filesystem>
#include <fstream>
#include <glm/vec3.hpp>
#include <iostream>
#include <span>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <io.h>
#include <stdio.h>
#else
#include <unistd.h>
#endif

struct CliArguments;

class CliManager {
  public:
    static bool save_png(const std::vector<std::vector<std::array<uint8_t, 3>>> &img, const std::string &filename);
    static bool loadFromFile(const std::filesystem::path &path, tinyobj::attrib_t &attributes, std::vector<tinyobj::shape_t> &shapes,
                             std::string &error);

    static bool loadFromStdin(tinyobj::attrib_t &attributes, std::vector<tinyobj::shape_t> &shapes, std::string &error);

    static bool stdHasOutputFile();
    static bool stdinHasData();

    static int run(std::span<const char *const> args);

    // TODO: write cli output to standard output
    static bool writeOutputFile(const std::filesystem::path &path, const std::vector<std::vector<std::array<uint8_t, 3>>> &data, const int height,
                                const int width);
};
