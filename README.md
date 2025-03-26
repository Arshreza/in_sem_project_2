# Tetris Game in C++

## Description
This is a console-based Tetris game written in C++ that features color support, increasing difficulty levels, and smooth gameplay mechanics.

## Features
- Tetromino blocks in various shapes and colors
- Dynamic speed increase as the player progresses through levels
- Scoring system with increasing difficulty
- Full game loop with game-over and restart functionality
- User-friendly controls for movement, rotation, and dropping pieces

## Controls
- **A** - Move Left
- **D** - Move Right
- **S** - Soft Drop
- **W** - Rotate Tetromino
- **Space** - Hard Drop (Instantly drops to the bottom)
- **R** - Restart Game
- **Q** - Quit Game

## How It Works
1. Blocks fall from the top of the board.
2. Players control the blocks using keyboard inputs.
3. When a row is completely filled, it clears and adds points to the score.
4. Every **100 points**, the level increases, making the game faster.
5. The game continues until the blocks stack up to the top of the board.

## Requirements
- Windows OS (For `conio.h` and `windows.h` support)
- C++ Compiler (g++, MSVC, or any compatible compiler)

## How to Compile and Run
1. Open a terminal or command prompt.
2. Compile the code using g++:
   ```sh
   g++ tetris.cpp -o tetris.exe
   ```
3. Run the compiled executable:
   ```sh
   tetris.exe
   ```

## Notes
- This game is designed for Windows because of `windows.h` dependencies.
- Colors might not work correctly on unsupported consoles.

Enjoy playing Tetris in the terminal!

