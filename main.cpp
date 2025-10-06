#include "fmt/base.h"
#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <string>

namespace fs = std::filesystem;

int total_files = 0;
int total_folders = 0;

void print_file(std::string path) {
  for (fs::directory_iterator it(path), end; it != end; ++it) {
    std::string current_path = it->path().string();

    if (it->is_directory()) {
      total_folders++;
      print_file(current_path);
    }

    if (it->is_regular_file()) {
      total_files++;
    }

    fmt::println("{}", current_path);
  }
}

int main(int argc, char *argv[]) {
  print_file(fs::current_path().string());
  fmt::println("Total folders: {}, Total files: {}", total_folders,
               total_files);
  return 0;
}
