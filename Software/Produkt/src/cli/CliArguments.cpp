#include "cli/CliArguments.h"
#include <cxxopts.hpp>
#include <iostream>

CliArguments CliArguments::parse(std::span<const char* const> args) {
    CliArguments cliArgs;
    cxxopts::Options options("Prisma++", "CLI for OBJ input and raytraced output");

    options.add_options()
        ("h,help", "./prisma-puls-plus < objectfile.obj > rytracedimg.png\n ./prisma-plus-plus -f objectfile.obj > rytracedimg.png")
        ("f,file", "Input file path", cxxopts::value<std::string>())
        ;

    auto result = options.parse(static_cast<int>(args.size()), args.data());

    if (result.count("help")) {
        std::cout << options.help() << "\n";
        cliArgs.helpRequested = true;
        return cliArgs;
    }

    if (!result.count("file")) {
        std::cout << "--file argument missing\n";
        return cliArgs;
    }

    cliArgs.file = result["file"].as<std::string>();
    //TODO: Check if string is valid path
    //TODO: Convert to path instead of string
    cliArgs.valid = true;
    return cliArgs;
}