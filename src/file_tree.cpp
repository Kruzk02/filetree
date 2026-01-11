#include <file_tree.h>
#include <algorithm>
#include <filesystem>
#include <format>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

bool FileTree::shouldInclude(const std::filesystem::directory_entry &entry, const Options &options) {
    const auto name = entry.path().filename().string();

    if (name.empty()) return false;
    if (!options.showAll && name.starts_with('.')) return false;
    if (options.dirsOnly && entry.is_regular_file()) return false;
    return true;
}

std::string FileTree::formatEntry(const std::filesystem::directory_entry &entry, const Options &options) {
    std::string name = entry.path().filename().string();

    if (options.fullPath && entry.is_regular_file()) {
        name = entry.path().string();
    }

    if (options.showDate) {
        name = formatDate(entry.last_write_time()) + "  " + name;
    }

    if (entry.is_directory()) {
        name += "/";
    }

    return name;
}

std::string FileTree::formatDate(const std::filesystem::file_time_type &time) {
    const auto sys = std::chrono::file_clock::to_sys(time);
    const std::time_t t = std::chrono::system_clock::to_time_t(sys);

    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return std::format("[{}]", buf);
}

std::vector<fs::directory_entry> FileTree::getEntries(const std::filesystem::path &path) {
    std::vector<fs::directory_entry> entries;

    for (constexpr auto opts = fs::directory_options::skip_permission_denied; const auto &entry:
         fs::directory_iterator(path, opts)) {
        entries.push_back(entry);
    }

    std::ranges::sort(entries.begin(), entries.end(), [](auto &a, auto &b) {
        return a.path().filename() < b.path().filename();
    });

    return entries;
}

std::vector<std::string> FileTree::buildRecursive(const std::filesystem::path &path,
                                                  const Options &options,
                                                  const std::string &prefix,
                                                  int depth) {
    std::vector<std::string> lines;
    std::vector<fs::directory_entry> entries;

    for (const auto& e : getEntries(path)) {
        if (shouldInclude(e, options)) {
            entries.push_back(e);
        }
    }

    if (options.reverseOrder) {
        std::ranges::reverse(entries);
    }

    for (size_t i = 0; i < entries.size(); i++) {
        const auto &entry = entries[i];
        const bool isLast = i == entries.size() - 1;

        if (options.maxDepth && depth >= options.maxDepth) {
            continue;
        }

        std::string line = prefix + (isLast ? "\u2514\u2500\u2500 " : "\u251C\u2500\u2500 ");
        line += formatEntry(entry, options);
        lines.push_back(line);

        if (entry.is_directory()) {
            totalFolders++;
            auto sub = buildRecursive(
                entry.path().string(),
                options,
                prefix + (isLast ? "  " : "\u2502 "),
                depth++);
            lines.insert(lines.end(), sub.begin(), sub.end());
        } else {
            totalFiles++;
        }
    }
    return lines;
}

std::vector<std::string> FileTree::build(const std::filesystem::path &path,
                                         const Options &options) {
    totalFiles = 0;
    totalFolders = 0;
    return buildRecursive(path, options, "", 0);
}
