#pragma once

#include "options.h"
#include "entryinfo.h"

#include <filesystem>

class Filtering {
public:
    static bool shouldInclude(const std::filesystem::directory_entry &entry,
                              const Options &options);

    static bool shouldInclude(const EntryInfo &entryInfo,
                              const Options &options);
};
