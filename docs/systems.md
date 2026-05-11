% Systems (Tracking & Interception)

## Plain explanation

Systems orchestrate the high-level simulation flow. `tracking` senses/estimates target state; `interception` runs guidance and steering to produce actuation for the missile.

## Code pointers

- `systems/tracking.h`, `systems/tracking.cpp`
- `systems/interception.h`, `systems/interception.cpp`

## Typical flow per frame

1. Tracking updates observed target state (with noise/latency if simulated).
2. Interception reads tracked target and missile state and computes guidance outputs.
3. Steering converts guidance outputs to missile state changes.
4. Physics/motion integrates positions.

## Problems we faced & solutions

- Problem: undefined references at link time to `computeLeadPosition`, `updatePID`, `applySteering`.
  - Solution: add missing source files to the build (we updated `Makefile` to include `guidance/*.cpp` and `targeting/*.cpp`).
- Problem: order-of-updates caused guidance to use stale data.
  - Solution: document and enforce the step order in the main loop: sense → guidance → actuation → integrate → commit previous-state.
