# CMAKE Minimum version
cmake_minimum_required(VERSION 3.8...3.26)

# Project metadata
project(Connect4 VERSION 1.0 DESCRIPTION "Connect 4 CLI game written in c++" LANGUAGES CXX)

# CMake Variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "-g -std=c++20")

# Variables
set(SOURCES src/color.cpp
			src/game.cpp
			src/global.cpp
			src/main.cpp
			src/player.cpp
			src/player_pair.cpp
			src/vector2.cpp
			src/board.cpp
			src/cell.cpp)

set(HEADERS	include/color.hpp
			include/game.hpp
			include/global.hpp
			include/player.hpp
			include/player_pair.hpp
			include/token.hpp
			include/vector2.hpp
			include/board.hpp
			include/cell.hpp)

# Building options
add_executable(Connect4 ${SOURCES} ${HEADERS})
