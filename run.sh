#!/bin/bash

clang -S -emit-llvm testcases/small_function.c -o small_function.ll

opt --load-pass-plugin ./build/libInlinerPass.so \
    --passes=hello-world \
    -disable-output \
    small_function.ll
