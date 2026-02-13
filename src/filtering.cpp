#include "filtering.h"

bool Filtering::shouldInclude(const std::filesystem::directory_entry &entry, const Options &options) {
    return shouldInclude(
        {
            entry.path().string(),
            entry.is_directory() ? EntryType::Directory : EntryType::File,
            entry.last_write_time()
        }, options);
}

bool Filtering::shouldInclude(const EntryInfo &entryInfo,
                              const Options &options) {
    const std::string name = entryInfo.path.filename().string();
    if (!options.showAll && name.starts_with('.')) return false;

    if (options.dirsOnly && entryInfo.type != EntryType::Directory) return false;

    if (options.ignores.contains(name))
        return false;

    return true;
}
