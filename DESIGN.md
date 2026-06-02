# Design

## Introduction

This project implements Function Inlining with Dead Code Elimination as an LLVM optimization pass.

The optimization is performed on LLVM Intermediate Representation (LLVM IR).

## Design Goals

* Reduce function call overhead
* Improve optimization opportunities
* Remove unused functions
* Preserve program correctness

## Architecture

Input LLVM IR

↓

Function Analysis

↓

Instruction Count Calculation

↓

Recursive Function Detection

↓

Inlining Decision

↓

Dead Code Elimination

↓

Optimized LLVM IR

## Inlining Criteria

A function is considered for inlining if:

* It is not recursive
* Instruction count is below a predefined threshold
* Function size is small

## Dead Code Elimination

After inlining:

* Unused functions are identified
* Functions with no remaining call sites are removed

## Expected Output

* Reduced number of function calls
* Simplified LLVM IR
* Removal of dead functions

