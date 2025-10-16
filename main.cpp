#include "fmt/base.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fmt/core.h>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct Total {
  int files = 0;
  int folders = 0;
};

Total total;

void print_tree(const std::string path, const std::string option);
void print_tree(const std::string path, const std::string option,
                std::string prefix);

int main(int argc, char *argv[]) {
  if (argc > 2) {
    fmt::println("Usage: {} <option>", argv[0]);
    return 1;
  }

  std::string current_path = fs::current_path().string();
  fmt::println("{}", current_path);

  print_tree(current_path, argv[1] == nullptr ? "" : argv[1]);

  fmt::println("Total numbers of folders: {} and files: {}", total.folders,
               total.files);
  return 0;
}

std::vector<fs::directory_entry> getDirectoryEntries(std::string path,
                                                     std::string option) {
  std::vector<fs::directory_entry> entries;

  for (const auto &entry : fs::directory_iterator(path)) {
    if (option != "-a" && option != "--all") {
      if (entry.path().filename().string()[0] == '.')
        continue;
    }
    entries.push_back(entry);
  }

  std::sort(entries.begin(), entries.end(), [](auto &a, auto &b) {
    return a.path().filename() < b.path().filename();
  });

  return entries;
}

void print_tree(const std::string path, const std::string option) {
  print_tree(path, option, "");
}

void print_tree(const std::string path, const std::string option,
                std::string prefix) {
  const auto entries = getDirectoryEntries(path, option);

  for (int i = 0; i < entries.size(); i++) {
    const auto &entry = entries[i];
    bool isLast = (i == entries.size() - 1);
    std::string name = entry.path().filename();

    fmt::println("{}{}{}{}", prefix,
                 (isLast ? "\u2514\u2500\u2500 " : "\u251C\u2500\u2500 "), name,
                 (entry.is_directory() ? "/" : ""));

    if (entry.is_directory()) {
      total.folders++;
      print_tree(entry.path(), option, prefix + (isLast ? "  " : "\u2502 "));
    }

    if (entry.is_regular_file()) {
      total.files++;
    }
  }
}
