# Evaluation

## Evaluation Methodology

The project is evaluated using multiple test programs representing different function characteristics.

The objective is to verify whether the optimization pass correctly identifies functions suitable for inlining and removes dead functions after optimization.

## Test Cases

### Test Case 1: small_function.c

Purpose:

Verify that a small function is selected for inlining.

Expected Result:

INLINE

---

### Test Case 2: large_function.c

Purpose:

Verify that a large function is not selected for inlining.

Expected Result:

SKIP

---

### Test Case 3: recursive.c

Purpose:

Verify that recursive functions are not inlined.

Expected Result:

SKIP

Reason:

Recursive expansion may lead to excessive code growth.

---

### Test Case 4: dead_function.c

Purpose:

Verify that unused functions are detected and removed.

Expected Result:

REMOVE

---

### Test Case 5: multiple_calls.c

Purpose:

Verify that a small function called from multiple locations can be considered for inlining.

Expected Result:

INLINE

---

## Expected Evaluation Table

| Test Case      | Instruction Count | Recursive | Decision |
| -------------- | ----------------- | --------- | -------- |
| small_function | Low               | No        | INLINE   |
| large_function | High              | No        | SKIP     |
| recursive      | Medium            | Yes       | SKIP     |
| dead_function  | N/A               | No        | REMOVE   |
| multiple_calls | Low               | No        | INLINE   |

## Performance Metrics

The following metrics are used:

* Number of functions analyzed
* Number of functions inlined
* Number of functions skipped
* Number of dead functions removed
* Reduction in function call sites

## Expected Outcome

The optimization pass should:

* Inline small functions
* Avoid recursive functions
* Remove unused functions
* Produce optimized LLVM IR

