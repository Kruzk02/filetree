#include "fmt/base.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fmt/core.h>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int total_files = 0;
int total_folders = 0;

void print_tree(std::string path, std::string prefix = "") {
  std::vector<fs::directory_entry> entries;

  for (const auto &entry : fs::directory_iterator(path)) {
    entries.push_back(entry);
  }

  std::sort(entries.begin(), entries.end(), [](auto &a, auto &b) {
    return a.path().filename() < b.path().filename();
  });

  for (int i = 0; i < entries.size(); i++) {
    const auto &entry = entries[i];
    bool isLast = (i == entries.size() - 1);
    std::string name = entry.path().filename();

    fmt::print("{}{}", prefix,
               (isLast ? "\u2514\u2500\u2500 " : "\u251C\u2500\u2500 "));
    fmt::println("{}{}", name, (entry.is_directory() ? "/" : ""));

    if (entry.is_directory()) {
      total_folders++;
      print_tree(entry.path(), prefix + (isLast ? "  " : "\u2502 "));
    }

    if (entry.is_regular_file()) {
      total_files++;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    fmt::println("Usage: {} <option>", argv[0]);
    return 1;
  }

  std::string current_path = fs::current_path().string();
  fmt::println("{}", current_path);
  print_tree(current_path);
  fmt::println("Total folders: {}, Total files: {}", total_folders,
               total_files);
  return 0;
}
