#pragma once

#include <file_tree.h>
#include <filesystem>

class Filtering {
public:
	bool shouldInclude(const std::filesystem::directory_entry& entry,
		const FileTree::Options& options);
};