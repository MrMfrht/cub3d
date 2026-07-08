# cub3D

A 42 school project implementing a 3D maze renderer using raycasting, inspired by the classic Wolfenstein 3D engine. Built in C using MiniLibX.

**Authors:** [fdaher](mailto:fdaher@student.42.fr) & [mofarhat](mailto:mofarhat@student.42.fr)

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Map Format](#map-format)
- [Test Cases](#test-cases)
- [Project Structure](#project-structure)

---

## About

cub3D renders a first-person 3D view of a maze defined by a `.cub` map file. The engine uses the Digital Differential Analyzer (DDA) raycasting algorithm to project 2D map walls into a 3D perspective with textured surfaces, colored floors, and colored ceilings.

## Features

- Textured walls using `.xpm` image files (North, South, East, West)
- Configurable floor and ceiling RGB colors
- Smooth player movement with wall collision detection
- Wall sliding (independent X/Y collision checks)
- Robust map parsing with detailed error messages
- Flood-fill map validation (ensures the map is fully enclosed)

## Requirements

- **OS:** Linux (X11 windowing system)
- **Compiler:** `gcc`
- **Libraries:** MiniLibX, X11, Xext, math, zlib
- **42 Libraries:** libft (included), get_next_line (included)

### Install dependencies (Debian/Ubuntu)

```bash
sudo apt-get install gcc make libx11-dev libxext-dev libbz2-dev
```

## Installation

1. Clone the repository:
```bash
git clone <repository-url> cub3d
cd cub3d
```

2. Install MiniLibX into the project directory:
```bash
git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux
cd minilibx-linux && make && cd ..
```

3. Build the project:
```bash
make
```

Other make targets:
| Command | Description |
|---------|-------------|
| `make` | Build the `cub3D` binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the binary |
| `make re` | Full rebuild |

## Usage

```bash
./cub3D <path_to_map.cub>
```

Example:
```bash
./cub3D maps/valid/v1.cub
```

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `Left Arrow` | Rotate camera left |
| `Right Arrow` | Rotate camera right |
| `ESC` | Quit |
| Window X button | Quit |

## Map Format

A `.cub` file has two sections: **texture/color definitions** and a **map grid**.

### Texture & Color Definitions

Six identifiers are required (order does not matter):

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
F <R>,<G>,<B>
C <R>,<G>,<B>
```

- Texture paths must point to existing `.xpm` files
- RGB values must be integers in the range `0-255`
- Each identifier must appear exactly once
- Blank lines and leading/trailing spaces between identifiers are allowed

### Map Grid

The map follows the texture definitions and uses these characters:

| Character | Meaning |
|-----------|---------|
| `0` | Walkable space |
| `1` | Wall |
| `N` | Player start (facing North) |
| `S` | Player start (facing South) |
| `E` | Player start (facing East) |
| `W` | Player start (facing West) |
| ` ` (space) | Void (outside the map) |

**Rules:**
- The map must be fully enclosed by walls (`1`)
- Exactly one player position is required
- No empty lines within the map
- First and last rows must contain only `1` and spaces
- Each row must start and end with `1` (after trimming spaces)
- The map does not need to be rectangular

### Example valid map (`maps/valid/v2.cub`)

```
NO ./image/green_wall.xpm
SO ./image/green_wall.xpm
WE ./image/stone_wall.xpm
EA ./image/stone_wall.xpm
C 0, 204, 255
F 101, 67, 33

111111
100101
101001
1100N1
111111
```

## Test Cases

The project includes test maps in `maps/valid/` and `maps/invalid/`.

### Valid Maps (should launch successfully)

```bash
./cub3D maps/valid/v1.cub    # Large complex map with irregular shape, player facing N
./cub3D maps/valid/v2.cub    # Small 6x5 enclosed map, player facing N
./cub3D maps/valid/v3.cub    # Large map variant, player facing N
```

### Invalid Maps (should print an error and exit)

| Test | Command | Expected Error |
|------|---------|----------------|
| Wrong file extension | `./cub3D maps/invalid/inv1.txt` | Wrong extension (not `.cub`) |
| Missing texture (EA) | `./cub3D maps/invalid/inv2.cub` | Missing `EA` identifier |
| Missing color (F) | `./cub3D maps/invalid/inv3.cub` | Missing `F` (floor color) |
| Wrong texture format | `./cub3D maps/invalid/inv4.cub` | `.png` instead of `.xpm` |
| Invalid map character | `./cub3D maps/invalid/inv5.cub` | Character `A` in the map |
| Empty line in map | `./cub3D maps/invalid/inv6.cub` | Gap (empty lines) inside map |
| Bad color + 2 players | `./cub3D maps/invalid/inv7.cub` | Incomplete `F` color & duplicate players |
| No map at all | `./cub3D maps/invalid/inv8.cub` | Only texture defs, no map grid |
| Open top border | `./cub3D maps/invalid/inv9.cub` | First row contains `0` (not enclosed) |
| Duplicate texture (WE) | `./cub3D maps/invalid/inv10.cub` | `WE` defined twice |
| Texture file not found | `./cub3D maps/invalid/inv11.cub` | `gree_wall.xpm` does not exist (typo) |

### Additional Edge Cases to Test Manually

```bash
# No arguments
./cub3D
# Expected: Error - Usage: ./cub3D map.cub

# Too many arguments
./cub3D maps/valid/v1.cub extra_arg
# Expected: Error - Usage: ./cub3D map.cub

# Non-existent file
./cub3D maps/valid/doesnotexist.cub
# Expected: Error - cannot open file

# Color out of range (value > 255 or < 0)
# Create a .cub file with: F 256, 0, 0
# Expected: Error - color out of range
```

## Project Structure

```
.
├── cub3d.h                     # Main header (structs, macros, prototypes)
├── makefile                    # Build system
├── get_next_line.c/h           # Line-by-line file reader
├── get_next_line_utils.c
├── image/
│   ├── green_wall.xpm          # Wall texture (green)
│   └── stone_wall.xpm          # Wall texture (stone)
├── libft/                      # 42 C utility library
├── maps/
│   ├── valid/                  # Valid test maps (v1-v3)
│   └── invalid/                # Invalid test maps (inv1-inv11)
├── minilibx-linux/             # MiniLibX graphics library (not included)
└── scr/
    ├── main.c                  # Entry point and game loop setup
    ├── parsing/
    │   ├── check.c             # File extension validation
    │   ├── get_input.c         # File reading into char** array
    │   ├── get_texture.c       # Texture path and color parsing
    │   ├── get_map.c           # Map extraction and line validation
    │   ├── get_rectangle.c     # Map rectangularization for engine
    │   ├── utils.c             # Texture checks, map start finder
    │   └── validation/
    │       ├── validate.c      # Flood-fill border validation
    │       ├── validate_utils.c    # Map padding, dimension helpers
    │       └── validate_utils2.c   # Player search, character checks
    ├── after_parsing/
    │   ├── init_map_player.c   # Map/player struct initialization
    │   ├── raycasting1.c       # Pixel put, floor/ceiling, DDA setup
    │   ├── raycasting2.c       # Wall distance, texture selection
    │   └── raycasting3.c       # Textured wall slice drawing
    └── render/
        ├── key_press.c         # Keyboard event handlers
        ├── player.c            # Movement, rotation, collision
        ├── render.c            # Main render loop
        ├── free_cub.c          # Memory cleanup
        └── init_utils/
            ├── init_cub.c      # Game state initialization
            ├── init_mlx.c      # Texture loading, image init
            └── init_mlx2.c     # Window creation, graphics setup
```
