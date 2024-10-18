#!/bin/bash

# specify the compiler
COMPILER=/opt/homebrew/Cellar/gcc/12.2.0/bin/g++-12

mkdir -p build  # create directory for out-of-source build
cd build || exit
cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_BUILD_TYPE=Release ..
cmake --build .