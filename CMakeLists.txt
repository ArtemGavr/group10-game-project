cmake_minimum_required(VERSION 3.16)
project(group10_game_project LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Compiler settings
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to a Debug build if the user didn't choose one.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Let clang-tidy / IDEs see the exact compile commands.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build the unit tests" ON)

# ---------------------------------------------------------------------------
# Game logic as a library, so the game AND the tests can both link to it.
# (main.cpp is NOT in here: the tests bring their own main from GoogleTest.)
# ---------------------------------------------------------------------------
add_library(game_lib game.cpp)
target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(game_lib PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>)

# ---------------------------------------------------------------------------
# The playable game
# ---------------------------------------------------------------------------
add_executable(game main.cpp)
target_link_libraries(game PRIVATE game_lib)

# ---------------------------------------------------------------------------
# Unit tests (GoogleTest, downloaded automatically at configure time)
# ---------------------------------------------------------------------------
if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  # Stop GoogleTest overriding our compiler/runtime settings on Windows.
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  # We only need GoogleTest, not GoogleMock, and we never install it.
  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  add_executable(game_tests tests/test_game.cpp)
  target_link_libraries(game_tests PRIVATE game_lib GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(game_tests)
endif()
