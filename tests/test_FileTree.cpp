#include <filesystem>
#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>

#include "../include/FileTree.h"

TEST_CASE("FileTree::build()", "FileTree") {
  FileTree fileTree;
  const auto res = fileTree.build(".", "");
  REQUIRE(!res.empty());
  REQUIRE(fileTree.getTotalFiles() > 0);
  REQUIRE(fileTree.getTotalFolders() > 0);
}
