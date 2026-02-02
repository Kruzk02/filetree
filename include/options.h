#pragma once

#include <optional>
#include <vector>
#include <string>

struct Options {
	bool showAll = false;
	bool dirsOnly = false;
	bool fullPath = false;
	bool showDate = false;
	std::optional<int> maxDepth;
	bool reverseOrder = false;
	std::string ignore;
};