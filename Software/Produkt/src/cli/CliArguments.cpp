#include "CliArguments.h"
#include <cxxopts.hpp>
#include <iostream>

CliArguments CliArguments::parse(int argc, const char* argv[]) {
    CliArguments args;
    cxxopts::Options options("Prisma++", "CLI for OBJ input and raytraced output");

    options.add_options()
        ("h,help", "./prisma-puls-plus < objectfile.obj > rytracedimg.png\n ./prisma-plus-plus -f objectfile.obj > rytracedimg.png")
        ("f,file", "Input file path", cxxopts::value<std::string>())
        ("v,verbose", "Verbose output")
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << "\n";
        args.helpRequested = true;
        return args;
    }

    if (!result.count("file")) {
        std::cerr << "Error: --file argument missing\n";
        return args;
    }

    args.file = result["file"].as<std::string>();
    args.valid = true;
    return args;
}