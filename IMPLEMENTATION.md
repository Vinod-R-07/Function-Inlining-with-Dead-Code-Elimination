# Implementation

## LLVM Pass Framework

The project is implemented as an LLVM optimization pass.

The pass operates on LLVM Intermediate Representation (LLVM IR) and analyzes every function present in the module.

## Function Analysis

For every function:

* Function name is collected
* Number of instructions is calculated
* Recursive behavior is detected
* Inlining eligibility is determined

## Inlining Heuristic

A function is considered for inlining when:

* The function is not recursive
* The instruction count is below the selected threshold
* The function body is sufficiently small

### Decision Rules

If:

Instruction Count ≤ Threshold

and

Function is Non-Recursive

Then:

INLINE

Otherwise:

SKIP

## Dead Code Elimination

After inlining:

* Functions with no remaining call sites are identified
* Unused functions are removed from the module

## Expected Benefits

* Reduced function call overhead
* Improved optimization opportunities
* Smaller execution path
* Cleaner LLVM IR

