% Angle Utilities

## Plain explanation

Helpers for wrapping and comparing angles. Because angles wrap at ±π, direct subtraction can yield large spurious numbers.

## Useful functions

- `wrapToPi(angle)` — normalize to [-π, π].
- `shortestAngleDiff(a, b)` — smallest signed difference from `a` to `b`.

## Code pointers

- `math/angle.h` and `math/angle.cpp`.

## Problems we faced & solutions

- Problem: sudden jump from +179° to -179° broke derivative computations.
  - Solution: always wrap differences to [-π, π] before using them for derivative or PID input.
