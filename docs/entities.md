% Entities (Drone & Missile)

## Plain explanation

`Drone` and `Missile` are simple data containers (positions, previous positions, velocities, state) used across systems. They don't contain complex logic—systems read/write them.

## Code pointers

- `entities/drone.h`, `entities/drone.cpp`
- `entities/missile.h`, `entities/missile.cpp`

## Implementation notes

- Keep entity structs plain and serializable for simple state stepping.
- Compute velocity from `prevX/prevY` when needed; update `prevX/prevY` each simulation step.

## Problems we faced & solutions

- Problem: inconsistent updates between `prevX/prevY` and current position caused wrong velocity estimates.
  - Solution: centralize update order in the simulation loop: compute guidance using current & prev, then apply motion, then set `prev = current` at end of step.
