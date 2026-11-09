cmake_minimum_required(VERSION 3.16)
project(group10_game_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build the test build (GoogleTest entry point)" ON)

# Release entry point: our real main()
add_executable(game main.cpp game.cpp)

# Test build only: GoogleTest's main() runs all tests
if(BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(
          googletest
          URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
          DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()
  add_executable(game_tests tests/test_game.cpp game.cpp)
  target_include_directories(game_tests PRIVATE ${CMAKE_SOURCE_DIR})
  target_link_libraries(game_tests PRIVATE GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(game_tests)
endif()