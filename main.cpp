#include "fmt/base.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fmt/core.h>
#include <string>
#include <string_view>
#include <vector>

#ifndef APP_VERSION
#define APP_VERSION "unknown"
#endif

namespace fs = std::filesystem;

struct Total {
  int files = 0;
  int folders = 0;
};

Total total;

std::vector<std::string> build_tree(const std::string &path,
                                    std::string_view option);

int main(int argc, char *argv[]) {
  if (argc > 2) {
    fmt::println("Usage: {} <option>", argv[0]);
    return 1;
  }

  std::string current_path = fs::current_path().string();

  auto tree = build_tree(current_path, argv[1] == nullptr ? "" : argv[1]);
  std::ranges::for_each(
      tree, [](std::string_view line) { fmt::println("{}", line); });

  fmt::println("Total numbers of folders: {} and files: {}", total.folders,
               total.files);
  return 0;
}

std::vector<fs::directory_entry> getDirectoryEntries(const std::string &path,
                                                     std::string_view option) {
  std::vector<fs::directory_entry> entries;

  for (const auto &entry : fs::directory_iterator(path)) {
    if (option != "-a" && option != "--all") {
      if (entry.path().filename().string()[0] == '.')
        continue;
    }

    if (option == "-d" || option == "--dirs-only") {
      if (entry.is_regular_file())
        continue;
    }

    entries.push_back(entry);
  }

  std::sort(entries.begin(), entries.end(), [](auto &a, auto &b) {
    return a.path().filename() < b.path().filename();
  });

  return entries;
}

std::vector<std::string> build_tree(const std::string &path,
                                    std::string_view option,
                                    const std::string &prefix) {
  std::vector<std::string> lines;
  const auto entries = getDirectoryEntries(path, option);

  for (int i = 0; i < entries.size(); i++) {
    const auto &entry = entries[i];
    bool isLast = (i == entries.size() - 1);
    std::string name = entry.path().filename();

    lines.push_back(prefix +
                    (isLast ? "\u2514\u2500\u2500 " : "\u251C\u2500\u2500 ") +
                    name + (entry.is_directory() ? "/" : ""));

    if (entry.is_directory()) {
      total.folders++;
      auto sublines = build_tree(entry.path(), option,
                                 prefix + (isLast ? "  " : "\u2502 "));
      lines.insert(lines.end(), sublines.begin(), sublines.end());
    }

    if (entry.is_regular_file()) {
      total.files++;
    }
  }
  return lines;
}

std::vector<std::string> build_tree(const std::string &path,
                                    std::string_view option) {

  if (option == "-v" || option == "--version") {
    fmt::println("Version: {}", APP_VERSION);
    exit(1);
  }

  fmt::println("{}", path);
  auto lines = build_tree(path, option, "");
  return lines;
}
