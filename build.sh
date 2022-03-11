#!/bin/bash

mkdir -p build # create directory for out-of-source build
cd build || exit 1
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release ..
cmake --build .