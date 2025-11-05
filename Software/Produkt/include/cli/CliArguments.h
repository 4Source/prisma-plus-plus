#pragma once
#include <cxxopts.hpp>
#include <filesystem>
#include <iostream>
#include <span>
#include <string>

// TODO: what arguments are needed
struct CliArguments {
    std::filesystem::path file;
    // valid Arguments gets set when given file has to be created
    bool createFile = true;
    bool helpRequested = false;

    static CliArguments parse(std::span<const char *const> args);
};