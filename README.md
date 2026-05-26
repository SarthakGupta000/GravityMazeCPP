# Gravity Maze

A terminal-based maze puzzle game where a constant downward gravity influences every move. Navigate the player (`S`) to the exit (`E`) while avoiding walls (`#`) — each turn you move and then gravity pulls you down.

## How to Run

```sh
make run
```

## Clean Up

```sh
make clean
```

## Features

- **Gravity mechanic** — every move is followed by a downward pull, adding a strategic layer to pathfinding
- **Turn-based input** — enter `U`, `D`, `L`, or `R` to move; invalid inputs are gracefully handled
- **Input validation** — out-of-bounds moves and wall collisions are caught, with clear feedback to the player
- **Clean separation of concerns** — game logic lives in `util.hpp` / `util.cpp`; the entry point in `main.cpp` stays minimal
- **Simple build system** — a straightforward `Makefile` handles compilation, execution, and cleanup
