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

  if (argv[1] == nullptr) {
    print_tree(current_path, "");
    return 0;
  }

  print_tree(current_path, argv[1]);
  fmt::println("Total numbers of folders: {} and files: {}", total.folders,
               total.files);
  return 0;
}

void print_tree(const std::string path, const std::string option) {
  print_tree(path, option, "");
}

void print_tree(const std::string path, const std::string option,
                std::string prefix = "") {
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
      total.folders++;
      print_tree(entry.path(), option, prefix + (isLast ? "  " : "\u2502 "));
    }

    if (entry.is_regular_file()) {
      total.files++;
    }
  }
}
