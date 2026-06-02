# Implementation

## Overview

The project is implemented as an LLVM Module Pass that performs cost-based function inlining and dead code elimination.

The pass traverses all functions in a module, computes an inlining cost, identifies call sites, performs function inlining using LLVM's `InlineFunction()` utility, removes dead functions, and eliminates unreachable basic blocks.

The implementation was developed using LLVM 18.1.3.

---

## Module Traversal

The pass operates on an LLVM Module.

For every function in the module:

* External declarations are skipped
* Function information is analyzed
* Inlining candidates are identified
* Call sites are examined

Implementation:

```cpp
for (Function &F : M) {
    if (F.isDeclaration())
        continue;

    visitor(F);
}
```

---

## Function Analysis

For every function, the pass computes:

* Function name
* Number of arguments
* Instruction count
* Recursive status
* Dead-function status

Instruction count is calculated by traversing all basic blocks and instructions.

Implementation:

```cpp
for (auto &BB : F)
    for (auto &I : BB)
        instructionCount++;
```

---

## Recursive Function Detection

Recursive functions are detected by examining call instructions inside the function body.

If a function calls itself, it is marked as recursive.

Implementation:

```cpp
if (CB->getCalledFunction() == &F)
    isRecursive = true;
```

Recursive functions are never considered for inlining.

---

## Inlining Cost Computation

The project uses instruction count as the inlining cost.

Rules:

* Cost < 10 → INLINE
* Cost ≥ 10 → SKIP

The cost is printed during analysis.

Example:

```text
Inlining Cost: 5
Decision: INLINE
```

---

## Call Site Analysis

The pass scans all instructions and identifies function call sites using LLVM's `CallBase` abstraction.

Implementation:

```cpp
if (auto *CB = dyn_cast<CallBase>(&I))
```

Call-site information is printed during execution.

Example:

```text
CALL SITE: main -> addOne
```

---

## Function Inlining

Inlining is performed using LLVM's `InlineFunction()` utility.

Implementation:

```cpp
InlineFunctionInfo IFI;
InlineFunction(*CB, IFI);
```

Successful inlining is reported as:

```text
INLINE SUCCESS
```

---

## Dead Function Elimination

After inlining, functions that have no remaining users are considered dead.

Dead functions are removed using:

```cpp
F->eraseFromParent();
```

Example:

```text
REMOVING: addOne
```

---

## Unreachable Block Elimination

Inlining may introduce unreachable basic blocks.

The pass removes such blocks using:

```cpp
removeUnreachableBlocks(F);
```

This simplifies the generated LLVM IR.

---

## LLVM APIs Used

* Module
* Function
* BasicBlock
* Instruction
* CallBase
* InlineFunction()
* InlineFunctionInfo
* eraseFromParent()
* removeUnreachableBlocks()

---

## Final Optimization Pipeline

```text
Module Analysis
       |
       v
Function Analysis
       |
       v
Cost Computation
       |
       v
Recursive Detection
       |
       v
Call Site Analysis
       |
       v
Function Inlining
       |
       v
Dead Function Elimination
       |
       v
Unreachable Block Elimination
       |
       v
Optimized LLVM IR
