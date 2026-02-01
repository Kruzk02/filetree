#include <file_tree.h>
#include <formatting.h>
#include <filtering.h>

#include <algorithm>
#include <filesystem>
#include <format>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

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
    Formatting formatting;
    Filtering filtering;

    std::vector<std::string> lines;
    std::vector<fs::directory_entry> entries;

    for (const auto& e : getEntries(path)) {
        if (filtering.shouldInclude(e, options)) {
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
        line += formatting.formatEntry(entry, options);
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
