#!/bin/zsh

mkdir build
conan install . --output-folder=build --build=missing --profile=default
cmake -B build
# Clangd includes
cp build/compile_commands.json .
