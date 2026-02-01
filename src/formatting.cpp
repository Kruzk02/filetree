#include <formatting.h>

namespace fs = std::filesystem;

std::string Formatting::formatDate(const std::filesystem::file_time_type& time) {
	using namespace std::chrono;

    auto sctp = time_point_cast<system_clock::duration>(
        time - fs::file_time_type::clock::now()
        + system_clock::now()
    );

    std::time_t t = system_clock::to_time_t(sctp);

    char buf[11];
    std::tm tm{};
    localtime_s(&tm, &t);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);

    return std::format("[{}]", buf);
}

std::string Formatting::formatEntry(const std::filesystem::directory_entry& entry,
	const Options& options) {
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