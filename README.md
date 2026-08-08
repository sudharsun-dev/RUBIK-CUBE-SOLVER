# 🧩 3D Rubik's Cube Solver in C++

A real-time **3D Rubik's Cube Solver built from scratch in C++**, combining cube algorithms, 3D graphics, interactive controls, and an automated solving system.

The project aims to simulate a fully functional Rubik's Cube in 3D, allow users to interact with the cube, generate scrambles, and automatically solve the cube while visually animating every move.

## 🚀 Features

* 🎲 Interactive 3D Rubik's Cube
* 🔄 Rotate and inspect the cube in 3D
* ⌨️ Keyboard controls for cube moves
* 🖱️ Mouse-controlled camera
* 🔀 Random scramble generation
* ↩️ Undo and reset functionality
* 🎨 Realistic cube colors and 3D rendering
* 🎬 Smooth move animations
* 🤖 Automated cube solver
* 📋 Display solution move sequence
* ▶️ Step-by-step solution playback
* 🖥️ Interactive GUI using Dear ImGui
* ⚡ C++-based cube engine and solver

## 🛠️ Tech Stack

* **C++**
* **OpenGL**
* **GLFW**
* **GLAD**
* **GLM**
* **Dear ImGui**
* **CMake**

## 🧠 How It Works

The project is divided into several major components:

```text
                    3D RUBIK'S CUBE SOLVER
                              │
             ┌────────────────┴────────────────┐
             │                                 │
        Cube Engine                         Renderer
             │                                 │
      Cube State / Moves                  OpenGL / GLM
             │                                 │
       Scramble / Undo                    3D Animation
             │                                 │
             └──────────────┬──────────────────┘
                            │
                          Solver
                            │
                    Solution Sequence
                            │
                            ↓
                     Move Animation
```

### Cube Engine

The cube is represented internally in C++ and supports standard Rubik's Cube moves:

```text
U  U'  U2
D  D'  D2
L  L'  L2
R  R'  R2
F  F'  F2
B  B'  B2
```

### 3D Renderer

OpenGL is used to render the cube as 27 individual cubelets.

The renderer handles:

* 3D transformations
* Camera movement
* Lighting
* Cubelet rendering
* Face rotation animations

### Solver

The solver receives the current cube state and produces a sequence of moves:

```text
Scrambled Cube
      ↓
Cube State
      ↓
Solver
      ↓
R U R' U' F2
      ↓
3D Animation
      ↓
Solved Cube
```

## 📅 Development Roadmap

### Phase 1: Cube Engine

* [x] Cube representation
* [x] Solved state
* [ ] U, D, L, R, F, B moves
* [ ] Prime and double moves
* [ ] Move validation
* [ ] Automated cube tests

### Phase 2: Cube System

* [ ] Move history
* [ ] Undo
* [ ] Reset
* [ ] Random scramble generator
* [ ] Cube state comparison
* [ ] Inverse move generation

### Phase 3: 3D Graphics

* [ ] OpenGL setup
* [ ] 3D cube rendering
* [ ] 27 cubelets
* [ ] Colored stickers
* [ ] Camera controls
* [ ] Lighting and visual effects

### Phase 4: Interaction & UI

* [ ] Keyboard controls
* [ ] Mouse controls
* [ ] Face rotation animation
* [ ] Scramble animation
* [ ] Dear ImGui interface
* [ ] Move history display
* [ ] Solution playback

### Phase 5: Solver

* [ ] Efficient cube representation
* [ ] Search-based solver
* [ ] Solver testing
* [ ] Solution optimization
* [ ] Solver + renderer integration
* [ ] Step-by-step solution animation

## 📂 Project Structure

```text
RubiksCubeSolver/
│
├── include/
│   ├── Cube.h
│   ├── Cubelet.h
│   ├── Solver.h
│   ├── Renderer.h
│   ├── Camera.h
│   └── Move.h
│
├── src/
│   ├── main.cpp
│   ├── Cube.cpp
│   ├── Cubelet.cpp
│   ├── Move.cpp
│   ├── Solver.cpp
│   ├── Renderer.cpp
│   ├── Camera.cpp
│   └── UI.cpp
│
├── shaders/
│   ├── vertex.glsl
│   └── fragment.glsl
│
├── assets/
│
├── CMakeLists.txt
│
└── README.md
```

## 🎯 Project Goal

The goal of this project is to understand how **data structures, algorithms, 3D mathematics, computer graphics, and software architecture** can be combined to build a complete interactive application.

Rather than treating the Rubik's Cube as only a visual object, the project maintains a separate internal cube state and uses that state as the source of truth for rendering, moves, scrambling, and solving.

## 🔮 Future Improvements

* Kociemba two-phase algorithm
* Shorter solution generation
* Faster solving using pruning tables
* Touch controls
* Custom cube-state input
* Timer and solve statistics
* Move counter
* Solution efficiency analysis
* Different cube sizes
* Improved 3D graphics
* Web-based version

## 📸 Demo

> Screenshots and demonstration videos will be added as development progresses.

## 📌 Status

🚧 **Currently in development**

This project is being developed incrementally over a **30-day roadmap**, starting with the cube engine and progressing toward a complete interactive 3D solver.

## 📄 License

This project is open-source and available under the MIT License.
