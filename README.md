# Function Inlining with Dead Code Elimination

## Project Overview

This project implements a cost-based Function Inlining and Dead Code Elimination pass using the LLVM compiler infrastructure.

The pass analyzes LLVM IR functions, computes an inlining cost based on instruction count, detects recursive functions, identifies call sites, performs function inlining using LLVM's `InlineFunction()` utility, removes dead functions created after inlining, and eliminates unreachable basic blocks.

The implementation was developed and tested using LLVM 18.1.3.

---

## Features

* Function analysis using LLVM IR
* Cost-based inlining heuristic
* Recursive function detection
* Function call-site analysis
* Function inlining using `InlineFunction()`
* Dead function elimination using `eraseFromParent()`
* Unreachable basic block elimination using `removeUnreachableBlocks()`

---

## Project Structure

```text
src/
└── InlinerPass.cpp

testcases/
├── small_function.c
├── large_function.c
├── recursive.c
├── dead_function.c
└── multiple_calls.c

README.md
DESIGN.md
IMPLEMENTATION.md
EVALUATION.md
build.sh
run.sh
CMakeLists.txt
```

---

## Build Instructions

Run:

```bash
./build.sh
```

or manually:

```bash
mkdir build
cd build
cmake .. -DLLVM_DIR=/usr/lib/llvm-18/lib/cmake/llvm
make
```

---

## Run Instructions

Run:

```bash
./run.sh
```

or manually:

```bash
opt --load-pass-plugin ./build/libInlinerPass.so \
    --passes=hello-world \
    -disable-output \
    input.ll
```

---

## Inlining Heuristic

The pass uses instruction count as the inlining cost.

Rules:

* Cost < 10 → INLINE
* Cost ≥ 10 → SKIP
* Recursive functions → SKIP

---

## Test Cases

1. small_function.c (should inline)
2. large_function.c (should not inline)
3. recursive.c (should be skipped)
4. dead_function.c (dead code elimination)
5. multiple_calls.c (multiple call-site analysis)

---

## LLVM APIs Used

* InlineFunction()
* InlineFunctionInfo
* eraseFromParent()
* removeUnreachableBlocks()
* CallBase
* Function
* Module

---

## Sample Output

```text
Function: add
Arguments: 2
Instructions: 8
Inlining Cost: 8
Recursive: NO
Dead Function: NO
Decision: INLINE

INLINE SUCCESS

REMOVING: add
```

---

## Author

Vinod R

Assignment 12 – Function Inlining with Dead Code Elimination

LLVM 18.1.3
