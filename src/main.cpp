#include "raylib.h"

// Define our premium aesthetic color palette
const Color COLOR_BG         = { 11, 13, 22, 255 };     // Fallback background color
const Color COLOR_GRID       = { 255, 255, 255, 15 };   // Super subtle base grid line
const Color COLOR_GRID_GLOW  = { 255, 255, 255, 5 };    // Ultra-soft wider glow line
const Color COLOR_CYAN       = { 0, 242, 254, 255 };    // Electric Cyan (#00f2fe)
const Color COLOR_PINK       = { 238, 9, 121, 255 };    // Hot Pink (#ee0979)
const Color COLOR_MUTED      = { 142, 142, 147, 255 };  // Steel Muted Grey (#8e8e93)
const Color COLOR_OVERLAY    = { 11, 13, 22, 200 };     // Semi-transparent overlay for game over screen

// Frame Panel Colors - Frosted glass purple
const Color COLOR_PANEL_BG   = { 15, 12, 30, 70 };      // Semi-transparent purple tint
const Color COLOR_FRAME      = { 157, 78, 221, 120 };   // Crisp neon purple border
const Color COLOR_FRAME_GLOW = { 123, 44, 191, 50 };    // Soft, wider purple glow

// The gameplay grid size remains a fixed, crisp 600x600 box
const int gridWidth = 600;
const int gridHeight = 600;
const int cellSize = 200;

// Board representation: 0 = Empty, 1 = Player X (Cyan), 2 = Player O (Pink)
int board[9] = { 0, 0, 0, 
                 0, 0, 0, 
                 0, 0, 0 };

int currentTurn = 1; // 1 = Player X, 2 = Player O
bool gameOver = false;
int winner = 0;      // 0 = None/Draw, 1 = Player X, 2 = Player O, -1 = Tie
int winPattern = -1; // Index of the winning line

bool CheckWin() {
    int winStates[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (int i = 0; i < 8; i++) {
        int a = winStates[i][0];
        int b = winStates[i][1];
        int c = winStates[i][2];

        if (board[a] != 0 && board[a] == board[b] && board[a] == board[c]) {
            winner = board[a];
            winPattern = i;
            return true;
        }
    }
    return false;
}

bool CheckTie() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) return false;
    }
    return true;
}

void DrawWinLine(Vector2 offset) {
    if (winPattern == -1) return;

    Vector2 start = { 0 };
    Vector2 end = { 0 };

    switch (winPattern) {
        case 0: start = { 50, 100 };  end = { 550, 100 }; break;
        case 1: start = { 50, 300 };  end = { 550, 300 }; break;
        case 2: start = { 50, 500 };  end = { 550, 500 }; break;
        case 3: start = { 100, 50 };  end = { 100, 550 }; break;
        case 4: start = { 300, 50 };  end = { 300, 550 }; break;
        case 5: start = { 500, 50 };  end = { 500, 550 }; break;
        case 6: start = { 70, 70 };    end = { 530, 530 }; break;
        case 7: start = { 530, 70 };   end = { 70, 530 };  break;
    }

    start.x += offset.x; start.y += offset.y;
    end.x += offset.x;   end.y += offset.y;

    Color winColor = (winner == 1) ? COLOR_CYAN : COLOR_PINK;
    DrawLineEx(start, end, 14.0f, { winColor.r, winColor.g, winColor.b, 60 });
    DrawLineEx(start, end, 6.0f, winColor);
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    
    InitWindow(gridWidth, gridHeight, "Aesthetic Tic-Tac-Toe");
    
    // --- 1. Initialize Audio Device ---
    InitAudioDevice(); 
    
    SetTargetFPS(60);

    // Load Assets
    Texture2D background = LoadTexture("C:\\Users\\Talha\\Desktop\\Tic-Tac-Toe\\assets\\bg.png"); 
    
    // --- 2. Load Sound Files ---
    Sound sndPlace = LoadSound("C:\\Users\\Talha\\Desktop\\Tic-Tac-Toe\\assets\\click.wav");
    Sound sndWin   = LoadSound("C:\\Users\\Talha\\Desktop\\Tic-Tac-Toe\\assets\\win.wav");
    Sound sndTie   = LoadSound("C:\\Users\\Talha\\Desktop\\Tic-Tac-Toe\\assets\\tie.wav");

    if (background.id > 0) {
        SetWindowSize(background.width, background.height);
    }

    while (!WindowShouldClose()) {
        int screenW = GetScreenWidth();
        int screenH = GetScreenHeight();

        Vector2 gridOrigin = {
            (float)(screenW - gridWidth) / 2.0f,
            (float)(screenH - gridHeight) / 2.0f
        };

        Vector2 mousePos = GetMousePosition();
        Vector2 relativeMousePos = {
            mousePos.x - gridOrigin.x,
            mousePos.y - gridOrigin.y
        };

        int col = relativeMousePos.x / cellSize;
        int row = relativeMousePos.y / cellSize;
        int hoveredCell = row * 3 + col;

        bool isMouseInGrid = (relativeMousePos.x >= 0 && relativeMousePos.x < gridWidth && 
                              relativeMousePos.y >= 0 && relativeMousePos.y < gridHeight);

        // ---------------------------------------------------------
        // UPDATE GAME LOGIC
        // ---------------------------------------------------------
        if (isMouseInGrid && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !gameOver) {
            if (board[hoveredCell] == 0) {
                board[hoveredCell] = currentTurn;
                
                if (CheckWin()) {
                    gameOver = true;
                    PlaySound(sndWin); // Play victory sound!
                } else if (CheckTie()) {
                    gameOver = true;
                    winner = -1; 
                    PlaySound(sndTie); // Play neutral draw sound!
                } else {
                    PlaySound(sndPlace); // Play placement sound!
                    currentTurn = (currentTurn == 1) ? 2 : 1;
                }
            }
        }

        if (IsKeyPressed(KEY_SPACE) || (GetTouchPointCount() >= 2)) {

            if (IsSoundPlaying(sndWin)) StopSound(sndWin);
            if (IsSoundPlaying(sndTie)) StopSound(sndTie);

            for (int i = 0; i < 9; i++) board[i] = 0;
            currentTurn = 1;
            gameOver = false;
            winner = 0;
            winPattern = -1;
            
            PlaySound(sndPlace); // Satisfying visual reset sound
        }

        // ---------------------------------------------------------
        // RENDER SCREEN
        // ---------------------------------------------------------
        BeginDrawing();
            ClearBackground(COLOR_BG);

            // Draw Background
            if (background.id > 0) {
                float bgX = (screenW - background.width) / 2.0f;
                float bgY = (screenH - background.height) / 2.0f;
                DrawTexture(background, bgX, bgY, WHITE);
            }

            // Draw Centered Frame Panel
            Rectangle panelRec = { gridOrigin.x - 12, gridOrigin.y - 12, (float)gridWidth + 24, (float)gridHeight + 24 };
            DrawRectangleRounded(panelRec, 0.03f, 8, COLOR_PANEL_BG);
            DrawRectangleRoundedLinesEx(panelRec, 0.03f, 8, 4.0f, COLOR_FRAME_GLOW);
            DrawRectangleRoundedLinesEx(panelRec, 0.03f, 8, 1.5f, COLOR_FRAME);

            // Draw Subtle Grid Lines
            for (int i = 1; i < 3; i++) {
                int pos = i * cellSize;
                DrawLineEx({gridOrigin.x + pos, gridOrigin.y}, {gridOrigin.x + pos, gridOrigin.y + gridHeight}, 6.0f, COLOR_GRID_GLOW);
                DrawLineEx({gridOrigin.x + pos, gridOrigin.y}, {gridOrigin.x + pos, gridOrigin.y + gridHeight}, 2.0f, COLOR_GRID);

                DrawLineEx({gridOrigin.x, gridOrigin.y + pos}, {gridOrigin.x + gridWidth, gridOrigin.y + pos}, 6.0f, COLOR_GRID_GLOW);
                DrawLineEx({gridOrigin.x, gridOrigin.y + pos}, {gridOrigin.x + gridWidth, gridOrigin.y + pos}, 2.0f, COLOR_GRID);
            }

            // Draw Hover Preview
            if (isMouseInGrid && !gameOver && board[hoveredCell] == 0) {
                int cX = gridOrigin.x + (hoveredCell % 3) * cellSize + cellSize / 2;
                int cY = gridOrigin.y + (hoveredCell / 3) * cellSize + cellSize / 2;
                Color previewColor = (currentTurn == 1) ? COLOR_CYAN : COLOR_PINK;
                previewColor.a = 35;
                DrawCircleLines(cX, cY, 40.0f, previewColor);
            }

            // Draw Centered Active Board Markers
            for (int i = 0; i < 9; i++) {
                if (board[i] == 0) continue;

                int cX = gridOrigin.x + (i % 3) * cellSize + cellSize / 2;
                int cY = gridOrigin.y + (i / 3) * cellSize + cellSize / 2;

                if (board[i] == 1) {
                    DrawLineEx({(float)cX - 40, (float)cY - 40}, {(float)cX + 40, (float)cY + 40}, 8.0f, COLOR_CYAN);
                    DrawLineEx({(float)cX + 40, (float)cY - 40}, {(float)cX - 40, (float)cY + 40}, 8.0f, COLOR_CYAN);
                } 
                else if (board[i] == 2) {
                    DrawCircleLines(cX, cY, 45.0f, COLOR_PINK);
                    DrawCircleLines(cX, cY, 46.0f, COLOR_PINK);
                }
            }

            // Draw Victory Line
            if (gameOver && winner > 0) {
                DrawWinLine(gridOrigin);
            }

            // Centered Game Over HUD
            if (gameOver) {
                DrawRectangleRounded(panelRec, 0.03f, 8, COLOR_OVERLAY);
                
                if (winner == 1) {
                    DrawText("CYAN WINS", gridOrigin.x + 155, gridOrigin.y + 230, 48, COLOR_CYAN);
                } else if (winner == 2) {
                    DrawText("PINK WINS", gridOrigin.x + 160, gridOrigin.y + 230, 48, COLOR_PINK);
                } else if (winner == -1) {
                    DrawText("TIE GAME", gridOrigin.x + 175, gridOrigin.y + 230, 48, COLOR_MUTED);
                }
                
                DrawText("TAP SCREEN OR PRESS SPACE TO PLAY AGAIN", gridOrigin.x + 105, gridOrigin.y + 320, 18, COLOR_MUTED);
            }

        EndDrawing();
    }

    // --- 3. Clean up loaded audio assets to prevent memory leaks ---
    UnloadSound(sndPlace);
    UnloadSound(sndWin);
    UnloadSound(sndTie);
    CloseAudioDevice(); // Shut down Raylib audio mixer cleanly

    UnloadTexture(background);
    CloseWindow();
    return 0;
}


/*
C:\raylib\w64devkit\bin\g++.exe src/main.cpp -o Tic-Tac-Toe.exe -O1 -Wall -I C:\raylib\raylib\src -L C:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm
*/