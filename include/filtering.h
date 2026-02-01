#pragma once

#include <options.h>

#include <filesystem>

class Filtering {
public:
	bool shouldInclude(const std::filesystem::directory_entry& entry,
		const Options& options);
};