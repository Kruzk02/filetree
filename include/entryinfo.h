#pragma once

#include <filesystem>

enum class EntryType { File, Directory, Other };

struct EntryInfo {
    std::filesystem::path path;
    EntryType type;
    std::filesystem::file_time_type lastWriteTime;
};

