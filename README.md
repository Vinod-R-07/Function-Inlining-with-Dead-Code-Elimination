# Function Inlining with Dead Code Elimination

## Project Overview

This project implements Function Inlining and Dead Code Elimination using the LLVM compiler infrastructure.

Function Inlining replaces calls to small functions with the function body itself, reducing function call overhead and enabling further optimizations.

Dead Code Elimination removes functions and code that become unused after inlining.

## Objectives

* Analyze functions in LLVM IR
* Identify functions suitable for inlining
* Detect recursive functions
* Inline small functions
* Remove dead functions after inlining
* Evaluate optimization effectiveness

## Project Structure

src/ - LLVM pass implementation

testcases/ - input programs used for evaluation

README.md - project overview

DESIGN.md - design details

IMPLEMENTATION.md - implementation details

EVALUATION.md - evaluation and results

## Test Cases

1. small_function.c
2. large_function.c
3. recursive.c
4. dead_function.c
5. multiple_calls.c

## Expected Workflow

Input Program

↓

Generate LLVM IR

↓

Function Analysis

↓

Inlining Decision

↓

Dead Code Elimination

↓

Optimized LLVM IR
