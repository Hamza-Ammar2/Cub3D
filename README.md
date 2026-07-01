# cub3D — 42 RayCaster

A first-person ray-casted maze renderer (Wolfenstein 3D style) built with C and miniLibX.

---

## 1. Folder framework

```
Cub3D/
├── Makefile              # all / clean / fclean / re / bonus, -Wall -Wextra -Werror
├── README.md
├── .gitignore
├── includes/
│   └── cub3d.h           # structs, prototypes, macros, keycodes
├── src/
│   ├── main.c            # entry point, arg check, top-level flow
│   ├── parsing/          # everything that reads the .cub file
│   │   ├── parse_scene.c     # extension check, open, dispatch lines
│   │   ├── parse_textures.c  # NO SO WE EA
│   │   ├── parse_colors.c    # F  C
│   │   ├── parse_map.c       # read map block into char **
│   │   └── validate_map.c    # closed map, chars, single spawn
│   ├── init/
│   │   └── init_game.c   # mlx boot, window, image, textures, player
│   ├── raycasting/
│   │   ├── raycaster.c   # DDA loop + wall column math
│   │   └── render.c      # per-frame compose (loop hook)
│   ├── player/
│   │   └── movement.c    # WASD + arrow rotation, collisions
│   ├── events/
│   │   └── hooks.c       # key press/release, close button, ESC
│   └── utils/
│       ├── errors.c      # error_exit, put_pixel
│       └── free.c        # free_game (no leaks!)
├── libft/                # copy your libft + its Makefile here
├── minilibx/             # miniLibX sources (or use system version)
├── textures/             # north/south/east/west .xpm
└── maps/
    ├── valid/            # maps that must load
    └── invalid/          # maps that must error cleanly
```

> The stub `.c` files compile and define the module boundaries — fill them in.

---

## 2. Logistical framework — the task list

### Phase 0 — Setup (do together, day 1)
- [ ] Confirm miniLibX builds on your machines (system vs source).
- [ ] Copy `libft` in and confirm `make -C libft` works.
- [ ] Get a plain window opening + closing cleanly (ESC + red cross).
- [ ] Agree on `struct` layout in `cub3d.h` (this is the contract between you).
- [ ] Agree on the Norm-safe style + commit/branch conventions.

### Phase 1 — Parsing (`.cub` → validated data)
- [ ] Argument check: exactly one arg, `.cub` extension.
- [ ] Read file line by line (use GNL from libft).
- [ ] Parse the 4 texture identifiers (`NO SO WE EA`) → store paths.
- [ ] Parse floor `F` and ceiling `C` colors → pack into ints. Range [0,255].
- [ ] Allow elements in any order, separated by blank lines / multiple spaces.
- [ ] Read the map block (always last) into `char **`, **preserving spaces**.
- [ ] Validate: only `0 1 N S E W space`, exactly one player start.
- [ ] Validate: map is fully closed by walls (flood-fill is the clean way).
- [ ] Every failure → `Error\n` + explicit message + clean exit, no leaks.

### Phase 2 — Engine setup
- [ ] Init mlx, window, and a single frame image buffer.
- [ ] `put_pixel` into the image (never `mlx_pixel_put` per-pixel — too slow).
- [ ] Load the 4 `.xpm` textures, keep their pixel data addressable.
- [ ] Place player: position (tile center), direction + camera plane from spawn.

### Phase 3 — Raycasting (the heart)
- [ ] For each screen column: compute ray direction from camera plane.
- [ ] DDA loop: step through the grid until you hit a `1`.
- [ ] Compute perpendicular wall distance (avoids fisheye).
- [ ] Determine wall side (N/S/E/W) from ray step + hit side.
- [ ] Compute wall strip height + draw start/end.
- [ ] Sample the correct texture column, draw the textured vertical strip.
- [ ] Fill ceiling color above, floor color below.

### Phase 4 — Controls & window
- [ ] Key press/release hooks → held-key flags for smooth movement.
- [ ] WASD translate position; block movement into walls (collision).
- [ ] Left/right arrows rotate direction vector + camera plane.
- [ ] ESC and the red cross both exit cleanly.
- [ ] Window stays smooth on focus change / minimize.

### Phase 5 — Polish & defense prep
- [ ] Norm pass on every file (bonus files included in norm!).
- [ ] `valgrind` clean: no leaks, no invalid reads/writes.
- [ ] Build a folder of nasty test maps (see `maps/invalid/`).
- [ ] Test weird `.cub` files: missing element, bad RGB, open map, spaces, etc.

### Bonus (only after 100% mandatory works — separate evaluation)
- Wall collisions (if not already), minimap, doors, animated sprites,
  mouse-look rotation. Put these in `*_bonus.{c,h}` with a `bonus` rule.

---

## 3. Options for splitting the work (2 people)

There are two natural, low-conflict seams in this project. Pick the split that
matches how you like to work.

### Option A — "Parsing vs Rendering" (recommended, cleanest seam)
- **Person 1 — Data / Parsing:** Phase 1 fully (all of `src/parsing/`),
  `errors.c`, `free.c`, and the map validation. Owns everything that turns the
  file into a validated `t_config`.
- **Person 2 — Engine / Rendering:** Phases 2–4 (`init`, `raycasting`,
  `player`, `events`). Owns everything that turns `t_config` into pixels.
- **The contract:** the `t_config`/`t_game` structs in `cub3d.h`. Freeze them
  together on day 1. Person 2 can hardcode a fake `t_config` to start rendering
  before parsing is done, so you work in parallel from hour one.

**Why it's good:** almost no file overlap → few merge conflicts, and each
person owns one clearly gradeable half at the defense.

### Option B — "Math vs Systems"
- **Person 1 — Math:** raycasting/DDA, wall height, texture sampling, player
  movement/rotation math. The person who enjoys the geometry.
- **Person 2 — Systems:** parsing, validation, mlx setup, event hooks, memory
  management, Makefile, error handling.

**Why:** plays to strengths if one of you loves math and the other loves plumbing.
Slightly more shared touching of `init`/`render`.

### Option C — "Pair the hard part, split the rest"
- **Together (pair-program):** the raycaster (Phase 3) — it's the hardest and
  most error-prone; two brains save days here.
- **Split solo:** Person 1 takes parsing + validation; Person 2 takes
  init + events + movement + Makefile/tests.

**Why:** de-risks the one part that most often blocks 42 students, while still
parallelizing the routine work.

> Whatever you pick: **agree on `cub3d.h` first**. The struct definitions are the
> interface between your two halves — changing them mid-project is the #1 source
> of pain.

---

## 4. Things to consider before you start

**Git hygiene (critical at 42):**
- Only what's in the repo is graded. Commit often, both of you push.
- Use branches (`feat/parsing`, `feat/raycaster`) + PRs/merges to avoid clobbering.
- **Never** commit `obj/`, the binary, or `.o`/`.a` (see `.gitignore`).
- **Do** commit `libft/` and `minilibx/` sources — the subject requires them.

**Norm & failure = 0:**
- Norm errors → 0, *including bonus files*. Run norminette continuously, not at the end.
- Any segfault / double free / leak during eval → 0. Test with `valgrind` early and often.
- Max 5 functions per file, 25 lines per function — plan your file split accordingly
  (the folder layout above already anticipates this).

**miniLibX gotchas:**
- Decide **system MLX vs source MLX** on day 1 — it changes your Makefile flags
  and keycodes. Linux (X11) and macOS have different keycodes and link flags
  (both variants are noted in the `Makefile` and `cub3d.h`).
- Only `.xpm` textures load natively. Get your 4 textures ready early.
- Render into **one image buffer** with `put_pixel`, then
  `mlx_put_image_to_window` once per frame. Per-pixel `mlx_pixel_put` is far too slow.
- Use `mlx_hook` for key press/release (held-key flags) rather than
  `mlx_key_hook` — you get smooth, simultaneous movement.

**Parsing is where most points are lost:**
- The map can contain spaces as valid cells — don't trim lines blindly.
- The map is always **last**; other elements can appear in any order with blank
  lines between them.
- Handle: missing/duplicate elements, bad RGB ranges, wrong extension, empty
  file, unreadable texture path, non-rectangular / open maps.
- Every error path must free everything and print `Error\n` + a real message.

**The math (don't over-think it):**
- This is a grid DDA raycaster. Read Lode Vandevenne's raycasting tutorial —
  it maps almost 1:1 onto this project. Understand *perpendicular* distance
  (kills the fisheye effect) and how the camera plane creates FOV.

**Workflow tips for two people:**
- Short daily sync: what each is doing + what struct fields you touched.
- Keep a shared list of test maps; break each other's parser on purpose.
- Integrate early: get a colored (untextured) wall on screen ASAP — momentum
  matters more than polish in week 1.

---

## Build

```bash
make        # build cub3D
make re     # rebuild from scratch
make clean  # remove objects
make fclean # remove objects + binary
./cub3D maps/valid/simple.cub
```
