#include <filetree.h>
#include <algorithm>
#include <filesystem>
#include <format>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::directory_entry> filetree::getEntries(const std::string &path) {
  std::vector<fs::directory_entry> entries;

  for (const auto &entry : fs::directory_iterator(path)) {
    entries.push_back(entry);
  }

  std::ranges::sort(entries.begin(), entries.end(), [](auto &a, auto &b) {
    return a.path().filename() < b.path().filename();
  });

  return entries;
}

std::string filetree::formatDate(const std::filesystem::file_time_type &entry) {
  const auto sys = std::chrono::file_clock::to_sys(entry);
  const std::time_t t = std::chrono::system_clock::to_time_t(sys);

  char buf[11];
  std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
  return std::format("[{}]", buf);
}

std::vector<std::string> filetree::buildRecursive(const std::string &path,
                                                  const std::string_view option,
                                                  const std::string &prefix) {
  const bool showAll  = option == "-a" || option == "--all";
  const bool dirsOnly = option == "-d" || option == "--dirs-only";
  const bool fullPath = option == "-f" || option == "--full-path";
  const bool showDate = option == "-D";

  std::vector<std::string> lines;
  const auto entries = getEntries(path);

  for (size_t i = 0; i < entries.size(); i++) {
    const auto &entry = entries[i];
    const bool isLast = i == entries.size() - 1;

    std::string name = entry.path().filename().string();
    if (name.empty()) continue;

    if (!showAll && name.starts_with('.')) continue;
    if (dirsOnly && entry.is_regular_file()) continue;

    if (fullPath && entry.is_directory()) name = entry.path().string();
    if (showDate) {
      const auto date = formatDate(entry.last_write_time()) += "  " + name;
      name.clear();
      name += date;
    }

    std::string line = prefix;
    line += isLast ? "\u2514\u2500\u2500 " : "\u251C\u2500\u2500 ";
    line += name;
    if (entry.is_directory()) line += "/";
    lines.push_back(line);

    if (entry.is_directory()) {
      totalFolders++;
      auto sub = buildRecursive(
        entry.path().string(),
        option,
        prefix + (isLast ? "  " : "\u2502 "));
      lines.insert(lines.end(), sub.begin(), sub.end());
    } else {
      totalFiles++;
    }
  }
  return lines;
}

std::vector<std::string> filetree::build(const std::string &path,
                                         const std::string_view option) {
  return buildRecursive(path, option, "");
}

int filetree::getTotalFiles() const {
  return totalFiles;
}

int filetree::getTotalFolders() const {
  return totalFolders;
}