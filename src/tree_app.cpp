#include <tree_app.h>
#include <file_tree.h>
#include <options.h>

#include <fmt/base.h>
#include <filesystem>
#include <string>
#include <string_view>

#include "fmt/format.h"

void TreeApp::showHelp() {
    fmt::println("Usage:");
    fmt::println("  tree [options] [path]\n");

    fmt::println("Description:");
    fmt::println("  Print a visual directory tree of the given path.");
    fmt::println("  If no path is provided, the current directory is used.\n");

    fmt::println("Options:");
    fmt::println("  {:<22}{}", "-a, --all", "Include hidden files and directories");
    fmt::println("  {:<22}{}", "-d, --dirs-only", "List directories only");
    fmt::println("  {:<22}{}", "-f, --full-path", "Print full path instead of filename");
    fmt::println("  {:<22}{}", "-D, --show-date", "Show last modified date");
    fmt::println("  {:<22}{}", "-L, --max-depth <N>", "Descend only N levels deep");

    fmt::println("\nMisc:");
    fmt::println("  {:<22}{}", "--help", "Show this help message and exit");
    fmt::println("  {:<22}{}", "--version", "Show version information and exit");
}

void TreeApp::showVersion() {
#ifdef APP_VERSION
    fmt::println("Version: {}", APP_VERSION);
#else
    fmt::println("Version: unknown");
#endif
}

Options TreeApp::parseOptions(int argc, char *argv[]) {
    Options opts;

    for (int i = 1; i < argc; ++i) {
        if (std::string_view arg{argv[i]}; arg == "-a" || arg == "--all") {
            opts.showAll = true;
        }
        else if (arg == "-d" || arg == "--dirs-only") {
            opts.dirsOnly = true;
        }
        else if (arg == "-f" || arg == "--full-path") {
            opts.fullPath = true;
        }
        else if (arg == "-D" || arg == "--show-date") {
            opts.showDate = true;
        }
        else if (arg == "-L" || arg == "--max-depth") {
            if (++i >= argc)
                throw std::runtime_error("-L requires a number");
            opts.maxDepth = std::stoi(argv[i]);
        } else if (arg == "-r" || arg == "--reverse-order") {
            opts.reverseOrder = true;
        }
        else {
            throw std::runtime_error(fmt::format("Unknown option: {}", arg));
        }
    }

    return opts;
}

int TreeApp::run(int argc, char *argv[]) {
    if (argc < 0) {
        fmt::println("Usage: tree [options]", argv[0]);
        return 1;
    }

    const std::string_view option{argc > 1 ? argv[1] : ""};
    if (option == "--help") {
        showHelp();
        return 0;
    }

    if (option == "--version") {
        showVersion();
        return 0;
    }

    std::string current_path = std::filesystem::current_path().string();
    fmt::println("{}", current_path);

    FileTree tree;
    for (auto lines = tree.build(current_path, parseOptions(argc, argv)); auto &line: lines)
        fmt::println("{}", line);

    fmt::println("Total folders: {} | Total files: {}", tree.getTotalFolders(),
                 tree.getTotalFiles());
    return 0;
}
