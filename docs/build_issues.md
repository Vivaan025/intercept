% Build & Common Issues

This file lists practical issues we hit while building and running the project and the steps used to fix or work around them.

1. Linker: undefined reference to functions implemented in other directories

- Symptom: linker errors like `undefined reference to computeLeadPosition`.
- Root cause: source files containing those symbols were not included in the compile command.
- Fix applied: update `Makefile` `SRC` to include `guidance/*.cpp` and `targeting/*.cpp` so the linker sees those object files.

2. Header include path differences between environments

- Symptom: compiler cannot find `pid.h` when building in WSL or Windows.
- Root cause: using angle-bracket include `#include <pid.h>` can make the compiler search system include paths first.
- Fix applied: use `#include "pid.h"` for local headers.

3. Redeclaration / compilation errors

- Symptom: `error: redeclaration of 'float dx'` in `targeting/lead.cpp`.
- Fix applied: remove duplicate declarations and reuse variables already defined earlier in the function.

4. Platform differences (WSL vs native Windows)

- Symptom: linking libraries like `-lGL -ldl` may behave differently on native Windows.
- Recommendation: build in WSL or adapt `Makefile` for native Windows toolchain (use `-lopengl32` and remove `-ldl`).

5. Noisy derivatives / numerical issues

- Symptom: jittery steering due to noisy LOS derivative.
- Fix: add small smoothing, clamp derivatives, or compute derivative over a window.

6. Timestep & integration

- Symptom: behaviour depends on frame rate.
- Fix: use explicit `dt` steps or document that simulation uses fixed-step updates; if needed, pass `dt` into `motion` functions.
