#include <catch2/catch_test_macros.hpp>

#include "formatting.h"
#include "options.h"
#include "catch2/matchers/catch_matchers.hpp"

TEST_CASE("Formatting::formatEntry") {
    Options opt;

    SECTION("full path included by default") {
        opt.fullPath = true;
        EntryInfo e{"asd/.hidden", EntryType::File, std::filesystem::file_time_type{}};
        CHECK(Formatting::formatEntry(e, opt) == "asd/.hidden");
    }

    SECTION("show date included by default") {
        opt.showDate = true;
        EntryInfo e{".hidden", EntryType::File, std::filesystem::file_time_type{}};
        CHECK(Formatting::formatEntry(e, opt) == "[2174-01-01]  .hidden");
    }

    SECTION("/ included on directory") {
        EntryInfo e{"hidden", EntryType::Directory, std::filesystem::file_time_type{}};
        CHECK(Formatting::formatEntry(e, opt) == "hidden/");
    }
}