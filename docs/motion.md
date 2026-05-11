% Motion & Physics

## Plain explanation

This module integrates position and velocity and applies simple accelerations. It models motion in 2D with position, velocity, and optionally simple drag or acceleration limits.

## Code pointers

- `physics/motion.h` and `physics/motion.cpp`.

## Problems we faced & solutions

- Problem: timestep assumptions (using unit dt) made behavior sensitive to frame rate.
  - Solution: clearly document and, if needed, pass `dt` explicitly into motion updates; for the simple sim we use constant discrete steps.
- Problem: inconsistent velocity initialization produced zero missile speed in closing-speed formulas.
  - Solution: ensure velocities are computed from `prevX/prevY` or explicitly initialized.
