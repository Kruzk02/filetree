#include <filesystem>
#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>

#include <file_tree.h>

TEST_CASE("FileTree::build() with no option", "No option") {
  FileTree fileTree;
  const auto res = fileTree.build(".", "");
  REQUIRE(!res.empty());
  REQUIRE(fileTree.getTotalFiles() > 0);
  REQUIRE(fileTree.getTotalFolders() > 0);
}

TEST_CASE("FileTree::build() with all option", "-a option") {
  FileTree fileTree;
  const auto res = fileTree.build(".", "-a");
  REQUIRE(!res.empty());
  REQUIRE(fileTree.getTotalFiles() > 0);
  REQUIRE(fileTree.getTotalFolders() > 0);
}

TEST_CASE("FileTree::build() with directory only option", "-d option") {
  FileTree fileTree;
  const auto res = fileTree.build(".", "-d");
  REQUIRE(!res.empty());
  REQUIRE(fileTree.getTotalFiles() == 0);
  REQUIRE(fileTree.getTotalFolders() > 0);
}

TEST_CASE("FileTree::build() with full path option", "-f option") {
  FileTree fileTree;
  const auto res = fileTree.build(".", "-f");
  REQUIRE(fileTree.getTotalFiles() > 0);
  REQUIRE(fileTree.getTotalFolders() > 0);
}
