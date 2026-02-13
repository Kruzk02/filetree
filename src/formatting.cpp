#include <format>
#include <formatting.h>

namespace fs = std::filesystem;

std::string Formatting::formatDate(const std::filesystem::file_time_type &time) {
    using namespace std::chrono;

    const auto sctp = time_point_cast<system_clock::duration>(
        time - fs::file_time_type::clock::now()
        + system_clock::now()
    );

    const std::time_t t = system_clock::to_time_t(sctp);

    char buf[11];
    std::tm tm{};
    localtime_s(&tm, &t);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);

    return std::format("[{}]", buf);
}

std::string Formatting::formatEntry(const std::filesystem::directory_entry &entry,
                                    const Options &options) {
    return formatEntry(
        {
            entry.path().string(),
            entry.is_directory() ? EntryType::Directory : EntryType::File,
            entry.last_write_time()
        }, options);
}

std::string Formatting::formatEntry(const EntryInfo &entryInfo, const Options &options) {
    std::string name = entryInfo.path.filename().string();

    if (options.fullPath && entryInfo.type == EntryType::File) {
        name = entryInfo.path.string();
    }

    if (options.showDate) {
        name = formatDate(entryInfo.lastWriteTime) + "  " + name;
    }

    if (entryInfo.type == EntryType::Directory) {
        name += "/";
    }

    return name;
}
