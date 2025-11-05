#pragma once
#include <string>
#include <span>

//TODO: what arguments are needed
struct CliArguments {
    std::string file;
    //valid Arguments gets set when file gets parsed successfully with --file option
    bool valid = false;
    bool helpRequested = false;

    static CliArguments parse(std::span<const char* const> args);
};