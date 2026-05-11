% Lead Computation (Target Prediction)

## Plain explanation

Lead computation predicts where the target will be after some time so the interceptor can aim at that future point rather than the target's current position.

## How it's used here

- We estimate target velocity from current and previous positions, predict future position using a small time horizon tied to relative speed, then compute an aim angle.

## Code pointers

- `targeting/lead.h` and `targeting/lead.cpp`.

## Problems we faced & solutions

- Problem: double-declared variables in `lead.cpp` caused compile errors (e.g., redeclaration of `dx/dy`).
  - Solution: reuse previously-declared `dx`/`dy` variables instead of re-declaring.
- Problem: naive time-to-intercept formula used target and missile speeds incorrectly leading to poor aim.
  - Solution: clamp the prediction horizon (max t) and compute a velocity-based horizon that matches missile dynamics.
