#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "filtering.h"
#include "options.h"

TEST_CASE("Filtering::shouldInclude") {
    Options opt;

    SUBCASE("hidden files excluded by default") {
        EntryInfo e{".hidden", EntryType::File, std::filesystem::file_time_type{}};
        CHECK_FALSE(Filtering::shouldInclude(e, opt));
    }

    SUBCASE("hidden files included with showAll") {
        opt.showAll = true;
        EntryInfo e{".hidden", EntryType::File, std::filesystem::file_time_type{}};
        CHECK(Filtering::shouldInclude(e, opt));
    }

    SUBCASE("dirsOnly excludes non-directories") {
        opt.dirsOnly = true;
        EntryInfo e{"file.txt", EntryType::File, std::filesystem::file_time_type{}};
        CHECK_FALSE(Filtering::shouldInclude(e, opt));
    }

    SUBCASE("dirsOnly includes directories") {
        opt.dirsOnly = true;
        EntryInfo e{"dir", EntryType::Directory, std::filesystem::file_time_type{}};
        CHECK(Filtering::shouldInclude(e, opt));
    }

    SUBCASE("ignores excludes by exact name") {
        opt.ignores.insert("file.txt");
        EntryInfo e{"file.txt", EntryType::File, std::filesystem::file_time_type{}};
        CHECK_FALSE(Filtering::shouldInclude(e, opt));
    }
}
