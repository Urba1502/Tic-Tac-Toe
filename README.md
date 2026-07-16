# Tic-Tac-Toe (C++ & Raylib)

A custom-themed Tic-Tac-Toe game built using **C++** and the **Raylib** graphics library.

## Features

- Styled grid layout with custom background
- Two-player turn-based system ($X$ and $O$)
- Responsive grid click detection
- Custom retro audio sound effects
- Turn indicators, win checking, and tie-game logic
- Smooth rendering powered by hardware acceleration

## Screenshots

### Gameplay

![Gameplay](assets/gameplay.png)

### Game Over

![Game Over](assets/win.png)

## Controls

| Key | Action |
|-----|--------|
| Left Mouse Click | Place Mark ($X$ or $O$) |
| R | Restart Game |
| Escape | Exit Game |

## Technologies Used

- C++
- Raylib
- Visual Studio Code
- Git & GitHub

## Project Structure

```
Tic-Tac-Toe/
│
├── assets/
│   ├── bg.png
│   ├── tie.png
│   ├── win.png
│   ├── screenshot .png
│   ├── click.wav
│   ├── tie.wav
│   └── win.wav
│
├── src/
│   └── main.cpp
│
└── README.md
```


## How to Build

1. Install Raylib.
2. Clone this repository:

```bash
git clone [https://github.com/Urba1502/Tic-Tac-Toe.git](https://github.com/Urba1502/Tic-Tac-Toe.git)

3. Open the project in Visual Studio Code.

4. Compile using g++:

```bash
g++ src/main.cpp -o Tic-Tac-Toe.exe ^
-I C:\raylib\raylib\src ^
-L C:\raylib\raylib\src ^
-lraylib -lopengl32 -lgdi32 -lwinmm
```


5. Run:

```bash
Tic-Tac-Toe.exe
```

## Author

**Urba1502**