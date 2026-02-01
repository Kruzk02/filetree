#pragma once
#include <string>
#include <filesystem>
#include <file_tree.h>

class Formatting {
public:
	std::string formatEntry(const std::filesystem::directory_entry &entry, 
		const FileTree::Options &options);
private:
	std::string formatDate(const std::filesystem::file_time_type& time);
};