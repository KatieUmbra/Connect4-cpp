# CMAKE Minimum version
cmake_minimum_required(VERSION 3.16...3.26)

# Project metadata
project(Connect4 VERSION 1.0 DESCRIPTION "Connect 4 CLI game written in c++" LANGUAGES CXX)

# CMake Variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "-I${CMAKE_SOURCE_DIR}/include -stdlib=libc++ -fsanitize=address")

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
			src/board.cpp
			src/cell.cpp
			src/scores.cpp)

set(HEADERS	include/color.hpp
			include/game.hpp
			include/global.hpp
			include/player.hpp
			include/player_pair.hpp
			include/token.hpp
			include/board.hpp
			include/cell.hpp
			include/scores.hpp)

set(PRECOMPILED_HEADERS		include/pch.hpp
							include/pch_tomlplusplus.hpp)

set(TEST_PCH		test/boost-test-pch.hpp)
set(TEST_SOURCES	test/game.cpp)

# Conan file
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Exporting compiler commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Libraries
find_package(Boost REQUIRED)
find_package(tomlplusplus REQUIRED)

# Building options
add_library(Binary ${SOURCES} ${HEADERS})
add_executable(Connect4 src/main.cpp)
target_link_libraries(Connect4 PRIVATE Binary tomlplusplus::tomlplusplus)
target_include_directories(Connect4 PRIVATE ${CONAN_LIBS})
target_precompile_headers(Connect4 PRIVATE ${PRECOMPILED_HEADERS})

# Testing binary
add_executable(Test ${TEST_SOURCES})
target_link_libraries(Test PRIVATE Binary boost::boost)
target_include_directories(Test PRIVATE ${CONAN_LIBS} ${Boost_INCLUDE_DIR})
target_precompile_headers(Test PRIVATE ${TEST_PCH})
