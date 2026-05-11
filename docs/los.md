% Line-Of-Sight (LOS)

## Plain explanation

LOS is the straight line between interceptor and target. Its angle and rate of change are the primary observables used by guidance laws like PN.

## Implementation notes

- Compute angle with `atan2(dy, dx)`.
- Compute LOS rate by differentiating LOS angle over time; take care with wrapping (angles cross the -pi/pi boundary).

## Code pointers

- `targeting/los.h` and `targeting/los.cpp`.

## Problems we faced & solutions

- Problem: discontinuities at the ±pi wrap boundary caused wrong large derivatives.
  - Solution: normalize angle differences using an angle-wrap helper (see `math/angle.*`).
- Problem: numeric noise made raw derivative unreliable.
  - Solution: use a small smoothing filter or compute derivative over multiple frames.
