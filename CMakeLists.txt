cmake_minimum_required(VERSION 3.16)
project(filetree)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 12.0.0)
FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE APP_SRC CONFIGURE_DEPENDS src/*.cpp)
add_executable(filetree ${APP_SRC} "src/formatting.cpp" "include/formatting.h" "include/filtering.h" "src/filtering.cpp")
target_include_directories(filetree PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(filetree PRIVATE fmt::fmt)
