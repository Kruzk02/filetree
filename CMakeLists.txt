cmake_minimum_required(VERSION 3.16)
project(filetree VERSION 1.0.0)

execute_process(
  COMMAND git describe --tags --dirty
  OUTPUT_VARIABLE GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 12.0.0)
FetchContent_MakeAvailable(fmt)

include(CTest)
enable_testing()

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.11.0)
FetchContent_MakeAvailable(Catch2)

add_executable(filetree_tests
        tests/test_main.cpp
        tests/test_filetree.cpp
        tests/test_TreeApp.cpp
        src/TreeApp.cpp
        src/FileTree.cpp
)

target_link_libraries(filetree_tests PRIVATE Catch2::Catch2WithMain fmt::fmt)

include(Catch)
catch_discover_tests(filetree_tests)

set(filetree_Version_Major 1)
set(filetree_Version_Minor 0)
set(filetree_Version_Patch 0)
set(filetree_Version_Status "-dev")

set(PROJECT_VERSION
    "${filetree_Version_Major}.${filetree_Version_Minor}.${filetree_Version_Patch}${filetree_Version_Status}+${GIT_VERSION}"
)

message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

add_executable(filetree src/main.cpp src/TreeApp.cpp src/FileTree.cpp)
target_include_directories(filetree PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(filetree PRIVATE fmt::fmt)
target_compile_definitions(filetree PRIVATE APP_VERSION="${GIT_VERSION}")
if(NOT CMAKE_BUILD_TYPE)
  set(default_build_type "Debug")
  message(
    STATUS
      "Set the build type to `${default_build_type}` as none was specified.")
  set(CMAKE_BUILD_TYPE
      ${default_build_type}
      CACHE STRING "Chooce the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "filetree Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for myProject
set(filetree_Version_Major 0)
set(filetree_Version_Minor 1)
set(filetree_Version_Patch 0)
set(filetree_Version_Status "-dev")
set(PROJECT_VERSION
    "${filetree_Version_Major}.${filetree_Version_Minor}.${filetree_Version_Patch}${filetree_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")
