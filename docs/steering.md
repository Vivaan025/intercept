% Steering & Actuation

## Plain explanation

The steering layer takes guidance commands (angles, accelerations) and converts them into updates to the missile's velocity/heading. It often uses a PID to apply commands smoothly and respect actuator limits.

## Relationship to guidance

- Guidance decides _where_ to go; steering decides _how_ to apply forces to reach that command without instability.

## Code pointers

- `guidance/steering.h` and `guidance/steering.cpp`.

## Problems we faced & solutions

- Problem: applying large guidance commands instantly caused unrealistic, unstable motion.
  - Solution: use PID smoothing and clamp outputs to physically plausible limits.
- Problem: large derivative spikes from noisy guidance inputs.
  - Solution: filter the guidance input or compute derivative on the actuator side with damping (D term).
