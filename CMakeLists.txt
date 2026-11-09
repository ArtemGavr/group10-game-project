cmake_minimum_required(VERSION 4.4)
project(group10_game_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(group10_game_project
        game.cpp
        game.h
        main.cpp)
