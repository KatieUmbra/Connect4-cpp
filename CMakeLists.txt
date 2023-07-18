# CMAKE Minimum version
cmake_minimum_required(VERSION 3.15...3.26)

# Project metadata
project(Connect4 VERSION 1.0 DESCRIPTION "Connect 4 CLI game written in c++" LANGUAGES CXX)

# CMake Variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "-g -std=c++20")

# CMake config
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Variables
set(SOURCES src/color.cpp
			src/game.cpp
			src/global.cpp
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

set(TEST_SOURCES	test/game.cpp)

# Building options
add_library(Binary ${SOURCES} ${HEADERS})
add_executable(Connect4 src/main.cpp)
target_link_libraries(Connect4 PRIVATE Binary)

# Including boost and conan files
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
find_package(Boost REQUIRED)

# Exporting compiler commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Testing binary
add_executable(Test ${TEST_SOURCES})
target_link_libraries(Test PRIVATE Binary ${CONAN_LIBS})
target_include_directories(Test PRIVATE ${Boost_INCLUDE_DIR})
