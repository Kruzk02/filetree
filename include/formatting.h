#pragma once

#include <options.h>

#include <string>
#include <filesystem>

class Formatting {
public:
	static std::string formatEntry(const std::filesystem::directory_entry &entry,
	                               const Options &options);
private:
	static std::string formatDate(const std::filesystem::file_time_type& time);
};