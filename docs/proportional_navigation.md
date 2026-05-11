% Proportional Navigation (PN)

## Plain explanation

Proportional Navigation is a guidance law: steer proportionally to how fast the line-of-sight (LOS) angle to the target is changing. If the LOS sweeps quickly, the interceptor must turn harder.

## Why it works

If the interceptor nulls the LOS rate (or counters it proportionally), the interceptor and target tend to meet at the same point in space.

## How it's applied here

- We compute LOS angle and LOS rate between missile and target.
- Commanded lateral acceleration (or turn rate) is proportional to LOS rate _ closing speed _ navigation constant (N).

## Code pointers

- `guidance/proportional_navigation.h` and `guidance/proportional_navigation.cpp`.

## Example (conceptual)

```
los = atan2(target.y - missile.y, target.x - missile.x)
los_rate = derivative(los)
command = N * closing_speed * los_rate
apply command via steering
```

## Problems we faced & solutions

- Problem: noisy LOS derivative produced jittery commands.
  - Solution: smooth LOS with a small low-pass filter or compute derivative via small-time-window regression instead of raw difference.
- Problem: too large navigation constant `N` produced overshoot.
  - Solution: pick moderate `N` (2–4 typical for simple missiles) and tune with simulations.
