#include "filtering.h"

bool Filtering::shouldInclude(const std::filesystem::directory_entry &entry, const Options &options) {
    return shouldInclude({entry.path().filename().string(), entry.is_directory()}, options);
}

bool Filtering::shouldInclude(const EntryInfo &entryInfo,
                              const Options &options) {
    if (!options.showAll && entryInfo.name.starts_with('.')) return false;

    if (options.dirsOnly && !entryInfo.isDir) return false;

    if (options.ignores.contains(entryInfo.name))
        return false;

    return true;
}
