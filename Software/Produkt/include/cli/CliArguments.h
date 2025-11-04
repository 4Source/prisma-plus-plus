#pragma once
#include <string>

struct CliArguments {
    std::string file;
    bool valid = false;
    bool helpRequested = false;

    static CliArguments parse(int argc, const char* argv[]);
};