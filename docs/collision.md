# Collision Detection

Collision detection decides when the missile and the drone are close enough to count as a hit.
When a collision happens, both entities are marked inactive and the simulation stops updating and rendering them.

## Physics Rule

This project uses a simple circle-to-circle distance check:

```text
distance = sqrt((drone.x - missile.x)^2 + (drone.y - missile.y)^2)
collision if distance < drone.radius + missile.radius
```

Each entity carries its own radius, so the hit test scales naturally with entity size.

## Implementation

The collision test lives in the physics module:

- [physics/collision.h](../physics/collision.h)
- [physics/collision.cpp](../physics/collision.cpp)

The interception system calls `checkCollision(drone, missile)` after the missile physics update.
If the check returns true, both entities are disabled:

```cpp
if (checkCollision(drone, missile)) {
	missile.active = false;
	drone.active = false;
}
```

## Rendering Behavior

Inactive entities are no longer drawn in the main loop.

```cpp
if (drone1.active) {
	drawObject(drone1.x, drone1.y, 0.2f, 0.8f, 0.3f);
}

if (missile.active) {
	drawObject(missile.x, missile.y, 1.0f, 0.0f, 0.0f);
}
```

## Summary

- Collision is handled by `checkCollision` in the physics layer.
- A hit disables both the drone and the missile.
- Dead entities stop updating and disappear from the screen.
