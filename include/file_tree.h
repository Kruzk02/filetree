#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

class FileTree {
public:
    struct Options {
        bool showAll   = false;
        bool dirsOnly  = false;
        bool fullPath  = false;
        bool showDate  = false;
    };

    static Options parseOptions(std::string_view option);

    std::vector<std::string> build(const std::filesystem::path &path,
                                   const Options &options);

    [[nodiscard]] int getTotalFiles() const noexcept {
        return totalFiles;
    }
    [[nodiscard]] int getTotalFolders() const noexcept {
        return totalFolders;
    }

private:
  static bool shouldInclude(const std::filesystem::directory_entry &entry,
      const Options& options);

  static std::string formatDate(const std::filesystem::file_time_type& time);

  static std::string formatEntry(const std::filesystem::directory_entry &entry,
      const Options& options);
  static std::vector<std::filesystem::directory_entry>
  getEntries(const std::filesystem::path &path);

  std::vector<std::string>
    buildRecursive(const std::filesystem::path &path,
                   const Options& options,
                   const std::string &prefix);


  int totalFiles = 0;
  int totalFolders = 0;

};
