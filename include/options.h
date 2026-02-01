#pragma once

#include <optional>

struct Options {
	bool showAll = false;
	bool dirsOnly = false;
	bool fullPath = false;
	bool showDate = false;
	std::optional<int> maxDepth;
	bool reverseOrder = false;
};