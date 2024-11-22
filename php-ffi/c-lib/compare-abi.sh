#!/usr/bin/env bash

rm -fr build pfx

CC=cc cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-Og" -DCMAKE_INSTALL_PREFIX="./pfx" && cmake --build build --target meddle-c && cmake --build build --target meddle-c -- install
cp ./pfx/lib/libmeddle-c.so ~/Apps/abi-complience-checker/libmeddle-gcc.so

rm -fr build pfx

CC=clang CXX=c++ cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-Og" -DCMAKE_INSTALL_PREFIX="./pfx" && cmake --build build --target meddle-c && cmake --build build --target meddle-c -- install
cp ./pfx/lib/libmeddle-c.so ~/Apps/abi-complience-checker/libmeddle-clang.so
