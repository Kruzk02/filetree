#include <filtering.h>

bool Filtering::shouldInclude(const std::filesystem::directory_entry& entry,
	const FileTree::Options& options) {
	const auto name = entry.path().filename().string();

	if (name.empty()) return false;
	if (!options.showAll && name.starts_with('.')) return false;
	if (options.dirsOnly && entry.is_regular_file()) return false;

	return true;
}