#!/bin/bash

mkdir -p build
cd build

cmake .. -DLLVM_DIR=/usr/lib/llvm-18/lib/cmake/llvm
make
