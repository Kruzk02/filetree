#include "../include/FileTree.h"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::directory_entry> FileTree::getEntries(const std::string &path,
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

std::vector<std::string> FileTree::buildRecursive(const std::string &path,
                                                  std::string_view option,
                                                  const std::string prefix) {
  std::vector<std::string> lines;
  auto entries = getEntries(path, option);

  for (size_t i = 0; i < entries.size(); i++) {
    const auto &entry = entries[i];
    bool isLast = (i == entries.size() - 1);
    std::string name = entry.path().filename();

    lines.push_back(prefix +
                    (isLast ? "\u2514\u2500\u2500 " : "\u251C\u2500\u2500 ") +
                    name + (entry.is_directory() ? "/" : ""));

    if (entry.is_directory()) {
      totalFolders++;
      auto sub = buildRecursive(entry.path().string(), option,
                                prefix + (isLast ? "  " : "\u2502 "));
      lines.insert(lines.end(), sub.begin(), sub.end());
    } else {
      totalFiles++;
    }
  }
  return lines;
}

std::vector<std::string> FileTree::build(const std::string &path,
                                         std::string_view option) {
  return buildRecursive(path, option, "");
}
