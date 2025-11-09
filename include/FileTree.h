#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

class FileTree {
public:
  std::vector<std::string> build(const std::string &path,
                                 std::string_view option);
  int getTotalFiles();
  int getTotalFolders();

private:
  std::vector<std::string> buildRecursive(const std::string &path,
                                          std::string_view option,
                                          const std::string prefix);
  std::vector<std::filesystem::directory_entry>
  getEntries(const std::string &path, std::string_view option);
  int totalFiles = 0;
  int totalFolders = 0;
};
