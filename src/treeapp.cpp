#include "../include/treeapp.h"
#include "../include/filetree.h"
#include "fmt/base.h"
#include <filesystem>
#include <string>
#include <string_view>

void treeapp::showHelp() {
  fmt::println("usage: tree <option>");
  fmt::println("  ------ Listing options ------");
  fmt::println("{:<16}{}", "  -a", "All files are listed.");
  fmt::println("{:<16}{}", "  -d", "List directories only.");

  fmt::println("  ------ Miscellaneous options ------");
  fmt::println("{:<16}{}", "  --version", "Print version and exit.");
  fmt::println("{:<16}{}", "  --help",
               "Print usage and this help message and exit.");
}

void treeapp::showVersion() {
#ifdef APP_VERSION
  fmt::println("Version: {}", APP_VERSION);
#else
  fmt::println("Version: unknown");
#endif
}

int treeapp::run(int argc, char *argv[]) {
  if (argc > 2) {
    fmt::println("Usage: {} <option>", argv[0]);
    return 1;
  }

  const std::string_view option = (argc > 1) ? argv[1] : "";
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

  filetree tree;
  for (auto lines = tree.build(current_path, option); auto &line : lines)
    fmt::println("{}", line);

  fmt::println("Total folders: {} | Total files: {}", tree.getTotalFolders(),
               tree.getTotalFiles());
  return 0;
}
