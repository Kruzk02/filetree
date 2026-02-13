#pragma once

#include "options.h"
#include "entryinfo.h"

#include <string>
#include <filesystem>

class Formatting {
public:

	static std::string formatEntry(const EntryInfo &entryInfo,
								   const Options &options);

	static std::string formatEntry(const std::filesystem::directory_entry &entry,
	                               const Options &options);

private:
	static std::string formatDate(const std::filesystem::file_time_type& time);
};
