# Tetris Game in C++

## Description
This is a console-based Tetris game written in C++ that features color support, increasing difficulty levels, and smooth gameplay mechanics.

## Features
- Tetromino blocks in various shapes and colors
- Dynamic speed increase as the player progresses through levels
- Scoring system with increasing difficulty
- Full game loop with game-over and restart functionality
- User-friendly controls for movement, rotation, and dropping pieces

## Screenshots
![Screenshot 2025-03-27 120101.png](<https://media-hosting.imagekit.io/a56df843b9734e9a/Screenshot%202025-03-27%20120101.png?Expires=1837665960&Key-Pair-Id=K2ZIVPTIP2VGHC&Signature=qw~qB6VTbP6OCPDRyJrzwdkQCmWU5qXXLRqiKKKTa5KEmju2gpPo4QIKXczLyzWJtVjaqyK~tFPjHv1BTGFW~3NcQaBwUQA3UznKLNHUuuZc2hebauGd056sTnlIytiAIUPMz3pyR6rAdIUbgppn8GXgYXuhCGEgMEoAf9YS8HYbSX9XQRB5DmTS5xDPCOqmPLPQhrl8LNd~mzjwBwrnYemXDZ4U-N5a8gFWmtdSxTmJ1QSz44696WsDNnM3E1vuz9GSJKXugFerKE7kTwlVkZAb-BOIOh9dGvpd3k7frhx6vPXkLHCrNdGK57IUMtrX~TnGEiNjH8nSx7X246Vulg__>)

![Screenshot 2025-03-27 120802.png](<https://media-hosting.imagekit.io/075d81fc7fa240e7/Screenshot%202025-03-27%20120802.png?Expires=1837666048&Key-Pair-Id=K2ZIVPTIP2VGHC&Signature=dgzxvQh~Zs8gSN6cW56F5C2F2WDRG8RjEQFG9iQQI2u519NwBz4j~kXoVVI8hH4zJF85RywY6XqnChulG-Ke9HUO4a~msK-A4bve3KdTfnYMoJAlFdv2Y3y7xHxvjprxcrLDk0vfXTTSeiSC-LbABt~MTDhbVqmshm~hVyI0qnLZBM5M4Dk8pTZFkr1Ala5~0Sw3XS1hmrOvsW8IwrbYj0ZyFYCNh~-0nscI0p92evx3Sgv1taf0lbiUd4QnAJUUQWBE99hW4mCIXlrLYa9HXRX4Oy2BuDxCFYGCn4MUPVq~qaAnHKhP2hb9amCXC2IRTXg1jXKc2-n9-tk7yjT-8w__>)  

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

