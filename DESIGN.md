# Design

## Introduction

This project implements a cost-based Function Inlining and Dead Code Elimination pass using LLVM.

The pass operates on LLVM Intermediate Representation (LLVM IR) and performs optimization by inlining small functions, removing dead functions generated after inlining, and eliminating unreachable basic blocks.

---

## Design Goals

* Reduce function call overhead
* Enable further compiler optimizations
* Remove unused functions
* Eliminate unreachable code
* Preserve program correctness
* Prevent recursive function inlining

---

## System Architecture

```text
Input LLVM IR
      |
      v
Module Traversal
      |
      v
Function Analysis
      |
      +------------------+
      |                  |
      v                  v
Instruction Count   Recursive Detection
      |                  |
      +--------+---------+
               |
               v
        Inlining Decision
               |
               v
       Call Site Analysis
               |
               v
        InlineFunction()
               |
               v
     Dead Function Removal
               |
               v
removeUnreachableBlocks()
               |
               v
      Optimized LLVM IR
```

---

## Function Analysis

For every function in the module, the pass computes:

* Function name
* Number of arguments
* Instruction count
* Recursive status
* Dead-function status

The instruction count is used as the inlining cost metric.

---

## Inlining Heuristic

The pass uses a simple cost-based heuristic.

### Inline Conditions

A function is considered for inlining when:

* The function is not recursive
* The function is defined in the module
* The instruction count is less than 10

### Skip Conditions

Inlining is skipped when:

* The function is recursive
* The instruction count is greater than or equal to 10
* The function declaration has no body

---

## Dead Code Elimination

After successful inlining:

* Functions with no remaining users are identified
* Such functions are removed using `eraseFromParent()`

This reduces code size and removes unnecessary definitions.

---

## Unreachable Block Elimination

Inlining may introduce unreachable basic blocks.

The pass removes unreachable blocks using:

```cpp
removeUnreachableBlocks()
```

This cleans up the generated LLVM IR.

---

## LLVM Components Used

* Module Pass
* Function
* BasicBlock
* CallBase
* InlineFunction()
* InlineFunctionInfo
* eraseFromParent()
* removeUnreachableBlocks()

---

## Expected Results

* Small functions are inlined
* Recursive functions are blocked
* Large functions are skipped
* Dead functions are removed
* Unreachable blocks are eliminated
* Optimized LLVM IR is generated

```
