# CMAKE Minimum version
cmake_minimum_required(VERSION 3.16...3.26)

# Project metadata
project(Connect4 VERSION 1.0 DESCRIPTION "Connect 4 CLI game written in c++" LANGUAGES CXX)

# CMake Variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE DEBUG)

if(MSVC)
set(CMAKE_CXX_FLAGS "/I ${CMAKE_SOURCE_DIR}\\include /I {CMAKE_SOURCE_DIR}\\libs\\tomlplusplus\\include")
else()
set(CMAKE_CXX_FLAGS "-I${CMAKE_SOURCE_DIR}/include -I{CMAKE_SOURCE_DIR}/libs/tomlplusplus/include")
endif()

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
			include/scores.hpp
			include/figlet.hpp)

set(PRECOMPILED_HEADERS		include/pch.hpp
							include/pch_tomlplusplus.hpp)

# Exporting compiler commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Building options
add_library(Binary ${SOURCES} ${HEADERS})
add_executable(Connect4 src/main.cpp)

target_include_directories(Binary PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(Connect4 PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Connect4 PRIVATE Binary)
target_include_directories(Connect4 PRIVATE ${CONAN_LIBS})
# Adding TomlPlusPlus 
target_include_directories(Binary PUBLIC ${CMAKE_SOURCE_DIR}/libs/tomlplusplus/include)
target_include_directories(Connect4 PUBLIC ${CMAKE_SOURCE_DIR}/libs/tomlplusplus/include)
target_precompile_headers(Connect4 PRIVATE ${PRECOMPILED_HEADERS})