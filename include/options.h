#pragma once

#include <optional>
#include <string>
#include <unordered_set>

struct Options {
    bool showAll = false;
    bool dirsOnly = false;
    bool fullPath = false;
    bool showDate = false;
    std::optional<int> maxDepth;
    bool reverseOrder = false;
    std::unordered_set<std::string> ignores;
};
