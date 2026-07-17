# cub3D

A Wolfenstein 3D-inspired raycasting engine written in C as part of the 42 curriculum. The project renders a 3D view from a 2D map using the MiniLibX graphics library and classic raycasting techniques.

## Features

- Raycasting-based 3D rendering
- Textured walls
- Map parsing and validation
- Player movement and rotation
- Configurable floor and ceiling colors
- Bonus version with additional features
- Memory leak-free implementation

## Concepts

- Raycasting
- Computer Graphics
- MiniLibX
- Texture Mapping
- Event Handling
- Parsing
- Linear Algebra
- Game Loop
- C Programming

## Project Structure

```
.
├── mandatory/
├── bonus/
├── libft/
├── minilibx-linux/
├── image/
└── Makefile
```

## Build

Build the mandatory version:

```bash
make
```

or

```bash
make all
```

Build the bonus version:

```bash
make bonus
```

## Run

Mandatory:

```bash
./cub3D maps/map.cub
```

Bonus:

```bash
./cub3d_bonus maps/map.cub
```

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make` | Build the mandatory version |
| `make all` | Build the mandatory version |
| `make bonus` | Build the bonus version |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executables |
| `make re` | Clean and rebuild the project |

## Controls

| Key | Action |
|------|--------|
| **W A S D** | Move |
| **← →** | Rotate |
| **ESC** | Exit |

## Resources

- 42 cub3D Subject
- MiniLibX Documentation
- Lode Vandevenne's Raycasting Tutorial
- Permadi's Raycasting Tutorial

## AI Usage

AI was used to:

- Review documentation.
- Improve grammar and readability.
- Assist with debugging and explaining raycasting concepts.

All implementation, algorithms, and project architecture were designed and implemented by [melayyad](https://github.com/simocv00) and [zouazrou](hhttps://github.com/zouazrou).