# Intercept — Concepts & Implementations

This document explains the main concepts used in this project, with short examples and pointers to where each concept is implemented in the codebase.

## PID (Control Theory)
- What it is: PID stands for Proportional-Integral-Derivative. It's a simple feedback controller that adjusts an output to reduce the difference (error) between a desired value and the current value.
- Simple example: imagine steering a car to keep it on the center of the road. If you're too far right, the controller steers left proportionally. The integral term corrects steady small offsets, and the derivative term smooths quick changes.
- How it's used here: we compute an `error` (difference between desired and actual angle/position) and pass it through a PID to produce a corrective command.
- Implementation: see [guidance/pid.h](guidance/pid.h#L1-L50) and [guidance/pid.cpp](guidance/pid.cpp#L1-L200).

### Tiny pseudo-example
```
error = desired_angle - current_angle
correction = updatePID(pid, error)
apply correction to actuator
```

## Proportional Navigation (PN)
- What it is: PN is a guidance law used for intercepting moving targets. The basic idea: turn the missile so the line-of-sight (LOS) rate to the target is nulled or reduced. The commanded acceleration is proportional to the LOS angular rate times closing speed.
- Simple example: if the target appears to move quickly across your view, rotate faster to keep it centered.
- How it's used here: PN computes the required turn/steering command to drive the missile toward the predicted intercept point.
- Implementation: see [guidance/proportional_navigation.h](guidance/proportional_navigation.h#L1-L200) and [guidance/proportional_navigation.cpp](guidance/proportional_navigation.cpp#L1-L200).

## Steering / Actuation
- What it is: the layer that converts guidance commands (angles/accelerations) into changes in the missile's state (velocity, heading). It may use PID controllers to smooth and limit commands.
- Simple example: guidance says "turn 10° left" → steering applies torque/steering angle gradually using PID to avoid oscillation.
- Implementation: see [guidance/steering.h](guidance/steering.h#L1-L200) and [guidance/steering.cpp](guidance/steering.cpp#L1-L200).

## Lead Computation (Target Prediction)
- What it is: predict where the target will be in the near future so the missile can aim at that point rather than current position.
- Simple example: if a drone moves right at 1 m/s and the missile takes 2 s to get there, aim 2 m to the right of the current drone position.
- Implementation: see [targeting/lead.h](targeting/lead.h#L1-L200) and [targeting/lead.cpp](targeting/lead.cpp#L1-L200).

## Line-Of-Sight (LOS)
- What it is: the straight line from the missile to the target. LOS angle and LOS rate are central to guidance laws like PN.
- Simple example: LOS angle = atan2(target.y - missile.y, target.x - missile.x).
- Implementation: see [targeting/los.h](targeting/los.h#L1-L200) and [targeting/los.cpp](targeting/los.cpp#L1-L200).

## Motion & Physics
- What it is: low-level integration of position, velocity, and simple physical dynamics used by both missile and target.
- Simple example: new_position = position + velocity * dt; velocity changes under applied acceleration.
- Implementation: see [physics/motion.h](physics/motion.h#L1-L200) and [physics/motion.cpp](physics/motion.cpp#L1-L200).

## Angle Utilities
- What it is: helper functions for wrapping, normalizing, and computing shortest-angle differences (useful to avoid sudden jumps from +179° to -179°).
- Simple example: shortest_angle = wrapToPi(target_angle - current_angle).
- Implementation: see [math/angle.h](math/angle.h#L1-L200) and [math/angle.cpp](math/angle.cpp#L1-L200).

## Entities (Drone & Missile)
- What they are: simple structs representing position, previous position, velocity, and state needed for guidance and simulation.
- How they interact: the system updates both entities each frame; guidance reads entity states and writes actuator commands for the missile.
- Implementation: see [entities/drone.h](entities/drone.h#L1-L200), [entities/drone.cpp](entities/drone.cpp#L1-L200), [entities/missile.h](entities/missile.h#L1-L200), and [entities/missile.cpp](entities/missile.cpp#L1-L200).

## Systems (Tracking & Interception)
- What they are: higher-level modules that orchestrate sensing, guidance, and actuation per simulation step.
- `tracking` updates perceived target position/velocity; `interception` runs guidance, leads, and steering to produce missile commands.
- Implementation: see [systems/tracking.h](systems/tracking.h#L1-L200), [systems/tracking.cpp](systems/tracking.cpp#L1-L200), [systems/interception.h](systems/interception.h#L1-L200), and [systems/interception.cpp](systems/interception.cpp#L1-L200).

## Renderer & Libraries
- Renderer: small wrapper to draw entities for visualization. See [renderer/renderer.cpp](renderer/renderer.cpp#L1-L200).
- External libs: OpenGL loader is in `libs/glad` and used for rendering setup.

## Quick Glossary (human language)
- Error: the difference between what you want and what you have.
- PID: a way to turn an error into a smooth correction using three terms (P, I, D).
- LOS: the line between the interceptor and the target.
- Lead: predicted future position of the target.
- PN: a guidance rule that uses LOS motion to steer the interceptor.

## Where to start reading the code
- For guidance basics: [guidance/pid.h](guidance/pid.h#L1-L50) and [guidance/proportional_navigation.h](guidance/proportional_navigation.h#L1-L50).
- For target prediction & LOS: [targeting/lead.cpp](targeting/lead.cpp#L1-L200) and [targeting/los.cpp](targeting/los.cpp#L1-L200).
- For the simulation loop: [main.cpp](main.cpp#L1-L200) and system files in `systems/`.

