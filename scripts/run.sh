#!/bin/zsh

cmake --build build --config Debug
clear
./build/bin/Connect4
