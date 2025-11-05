#include "cli/CliArguments.h"

/// @brief parses command line options
/// @param args 
/// @return 
CliArguments CliArguments::parse(std::span<const char *const> args) {
    CliArguments cliArgs;
    cxxopts::Options options("Prisma++", "CLI for OBJ input and raytraced output");

    options.add_options()("h,help", "./prisma-puls-plus < objectfile.obj --file rytracedimg.png\n ./prisma-plus-plus for ui run")(
        "f,file", "Input file path", cxxopts::value<std::string>());

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
    // check for valid path
    std::string filepathStr = result["file"].as<std::string>();
    cliArgs.file = filepathStr;
    if (std::filesystem::exists(cliArgs.file))
        cliArgs.createFile = false;

    return cliArgs;
}