#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

class filetree {
public:
  std::vector<std::string> build(const std::string &path,
                                 std::string_view option);
  [[nodiscard]] int getTotalFiles() const;
  [[nodiscard]] int getTotalFolders() const;

private:
  std::vector<std::string> buildRecursive(const std::string &path,
                                          std::string_view option,
                                          const std::string &prefix);
  static std::vector<std::filesystem::directory_entry>
  getEntries(const std::string &path);
  int totalFiles = 0;
  int totalFolders = 0;
};
