#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>

TEST_CASE("fmt works correctly", "[fmt]") {
  auto msg = fmt::format("Hello {}", "World");
  REQUIRE(msg == "Hello World");
}
