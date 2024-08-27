#!/usr/bin/env bash

cmake -S . -B build -DCMAKE_INSTALL_PREFIX="./pfx" && cmake --build build && cmake --build build -- install
