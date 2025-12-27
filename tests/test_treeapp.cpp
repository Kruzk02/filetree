#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>
#include <tree_app.h>
#include <string>
#include <iostream>

TEST_CASE("TreeApp::run with --help", "[TreeApp]") {
  const char *argv[] = { "treeapp", "--help" };
  const int result = TreeApp::run(2, const_cast<char**>(argv));
  REQUIRE(result == 0);
}

TEST_CASE("TreeApp::run with --version", "[TreeApp]") {
  const char *argv[] = { "treeapp", "--version" };
  const int result = TreeApp::run(2, const_cast<char**>(argv));
  REQUIRE(result == 0);
}

// TEST_CASE("TreeApp::run with unknown argument", "[TreeApp]") {
//   const char *argv[] = { "treeapp", "--qbwdoiqbwd" };
//   const int result = TreeApp::run(2, const_cast<char**>(argv));
//   REQUIRE(result == 1);
// }

TEST_CASE("TreeApp::run with no arguments", "[TreeApp]") {
  const char *argv[] = { "treeapp" };
  const int result = TreeApp::run(1, const_cast<char**>(argv));
  REQUIRE(result == 0);
}