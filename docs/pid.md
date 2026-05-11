% PID (Proportional–Integral–Derivative)

## What it is (plain language)

PID is a control recipe that turns a measured error into a corrective command using three terms:

- Proportional (P): push back in proportion to the error now.
- Integral (I): correct accumulated past error (removes steady offsets).
- Derivative (D): resist rapid changes (damps oscillation).

## Why we use it here

We use PID to convert angle/heading errors into smooth steering commands for the missile actuators so the guidance commands don't cause oscillation or instability.

## Key variables & code pointers

- The `PID` struct: `guidance/pid.h` contains `kp`, `ki`, `kd`, `integral`, and `prevError`.
- The updater: `guidance/pid.cpp` implements `updatePID(PID& pid, float error)`.

## Simple conceptual example

1. Compute error: `error = desired_angle - current_angle` (wrap angles to -pi..pi).
2. Send to PID: `u = updatePID(pid, error)`.
3. Apply `u` to steer/saturate as needed.

## Implementation notes

- Integral windup: we clamp `pid.integral` to a max value to avoid runaway.
- We compute derivative from the change in error; derivative on measurement avoids sudden spikes.

## Problems we faced & solutions

- Problem: `#include <pid.h>` caused compiler to search system include paths and fail on some toolchains.
  - Solution: change to `#include "pid.h"` so the local header is loaded consistently across WSL and Windows.
- Problem: incorrect PID gains caused oscillatory behaviour in early tests.
  - Solution: tune `kp/ki/kd` starting from pure-P, add small D to damp, then introduce I only if steady offset exists.

## Quick tuning tips

- Start with `kp` only. Increase until you get a reasonable response but not oscillation.
- Add `kd` to reduce overshoot; add `ki` last and keep it small.
