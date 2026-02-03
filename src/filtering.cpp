#include "filtering.h"

bool Filtering::shouldInclude(const std::filesystem::directory_entry& entry,
	const Options& options) {
	const std::string name = entry.path().filename().string();

	if (!options.showAll && name.starts_with('.')) return false;

	std::error_code ec;
	if (options.dirsOnly && !entry.is_directory(ec)) return false;

	if (options.ignores.contains(name))
		return false;

	return true;
}