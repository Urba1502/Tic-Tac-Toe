# ❌ Tic-Tac-Toe (Raylib) ⭕

![Tic Tac Toe Gameplay](assets/screenshot.png)

A custom-themed, graphical Tic-Tac-Toe game built in C++ using the **Raylib** library. This version features custom visual grids, a stylized background, and responsive retro sound effects for game states.

## 🎮 Features
* **Custom Aesthetic Theme:** Visually styled grid and high-quality background art.
* **Audio Integration:** Dedicated sound effects (`.wav`) for grid clicks, winning, and tie game states.
* **Responsive Layout:** Smooth rendering powered by Raylib's hardware acceleration.

---

## 🛠️ Requirements & Setup

To compile and run this project, you will need:
* A C++ compiler (like `g++` via MinGW on Windows).
* The **Raylib** development library installed.

### Compilation
You can compile the project from your terminal using the following command (adjust paths if your Raylib setup is located elsewhere):

```bash
g++ src/main.cpp -o Tic-Tac-Toe.exe -lraylib -lopengl32 -lgdi32 -lwinmm