# Function Inlining with Dead Code Elimination

## Overview

This project implements an LLVM optimization pass that performs Function Inlining and Dead Code Elimination.

Function Inlining replaces calls to small functions with the function body itself, reducing function call overhead and enabling further optimizations.

Dead Code Elimination removes functions and code that become unused after inlining.

## Features

* Cost-based function inlining
* Recursive function detection
* Dead function removal
* LLVM IR transformation
* Multiple test cases

## Test Cases

1. small_function.c
2. large_function.c
3. recursive.c
4. dead_function.c
5. multiple_calls.c

## Build

```bash
./build.sh
```

## Run

```bash
./run.sh
```
