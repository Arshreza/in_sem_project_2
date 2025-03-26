#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>
#include <algorithm>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int BASE_SPEED = 1000;
const int MIN_SPEED = 100;
const int LEVEL_SCORE = 100;
const int SPEED_DECREMENT = 100;

enum class TetrominoType { I, J, L, O, S, T, Z };

// Color codes for Windows console
enum ConsoleColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

class Tetromino {
private:
    TetrominoType type;
    int x, y;
    std::vector<std::vector<bool>> shape;

public:
    Tetromino() : x(0), y(0) {}
    
    TetrominoType getType() const { return type; }
    void setType(TetrominoType newType) { type = newType; }
    
    int getX() const { return x; }
    void setX(int newX) { x = newX; }
    
    int getY() const { return y; }
    void setY(int newY) { y = newY; }
    
    const std::vector<std::vector<bool>>& getShape() const { return shape; }
    void setShape(const std::vector<std::vector<bool>>& newShape) { shape = newShape; }

    ConsoleColor getColor() const {
        switch (type) {
            case TetrominoType::O: return YELLOW;
            case TetrominoType::I: return LIGHT_BLUE;
            case TetrominoType::S: return LIGHT_RED;
            case TetrominoType::Z: return LIGHT_GREEN;
            case TetrominoType::L: return YELLOW; // Orange not available, using yellow
            case TetrominoType::J: return LIGHT_MAGENTA; // Pink
            case TetrominoType::T: return MAGENTA; // Purple
            default: return WHITE;
        }
    }
};

std::vector<std::vector<bool>> board(BOARD_HEIGHT, std::vector<bool>(BOARD_WIDTH, false));
std::vector<std::vector<ConsoleColor>> boardColors(BOARD_HEIGHT, std::vector<ConsoleColor>(BOARD_WIDTH, BLACK));
Tetromino currentPiece;
int score = 0;
int level = 1;
bool gameOver = false;

void setColor(ConsoleColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void initializeTetromino(Tetromino& tetromino) {
    tetromino.setX(BOARD_WIDTH / 2 - 2);
    tetromino.setY(0);
    switch (tetromino.getType()) {
        case TetrominoType::I: tetromino.setShape({{true, true, true, true}}); break;
        case TetrominoType::J: tetromino.setShape({{true, false, false}, {true, true, true}}); break;
        case TetrominoType::L: tetromino.setShape({{false, false, true}, {true, true, true}}); break;
        case TetrominoType::O: tetromino.setShape({{true, true}, {true, true}}); break;
        case TetrominoType::S: tetromino.setShape({{false, true, true}, {true, true, false}}); break;
        case TetrominoType::T: tetromino.setShape({{false, true, false}, {true, true, true}}); break;
        case TetrominoType::Z: tetromino.setShape({{true, true, false}, {false, true, true}}); break;
    }
}

TetrominoType getRandomTetrominoType() {
    return static_cast<TetrominoType>(rand() % 7);
}

void spawnNewPiece() {
    currentPiece.setType(getRandomTetrominoType());
    initializeTetromino(currentPiece);
}

bool isCollision() {
    const auto& shape = currentPiece.getShape();
    for (size_t y = 0; y < shape.size(); ++y) {
        for (size_t x = 0; x < shape[y].size(); ++x) {
            if (shape[y][x]) {
                int boardX = currentPiece.getX() + x;
                int boardY = currentPiece.getY() + y;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT ||
                    (boardY >= 0 && board[boardY][boardX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mergePieceToBoard() {
    const auto& shape = currentPiece.getShape();
    ConsoleColor color = currentPiece.getColor();
    for (size_t y = 0; y < shape.size(); ++y) {
        for (size_t x = 0; x < shape[y].size(); ++x) {
            if (shape[y][x]) {
                board[currentPiece.getY() + y][currentPiece.getX() + x] = true;
                boardColors[currentPiece.getY() + y][currentPiece.getX() + x] = color;
            }
        }
    }
}

void clearLines() {
    int linesCleared = 0;
    for (int y = BOARD_HEIGHT - 1; y >= 0; --y) {
        bool lineFull = true;
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (!board[y][x]) {
                lineFull = false;
                break;
            }
        }
        if (lineFull) {
            linesCleared++;
            for (int yy = y; yy > 0; --yy) {
                board[yy] = board[yy - 1];
                boardColors[yy] = boardColors[yy - 1];
            }
            board[0] = std::vector<bool>(BOARD_WIDTH, false);
            boardColors[0] = std::vector<ConsoleColor>(BOARD_WIDTH, BLACK);
            ++y;
        }
    }
    
    if (linesCleared > 0) {
        int points = 0;
        switch (linesCleared) {
            case 1: points = 100; break;
            case 2: points = 300; break;
            case 3: points = 500; break;
            case 4: points = 800; break;
        }
        score += points;
        
        int newLevel = score / LEVEL_SCORE + 1;
        if (newLevel > level) {
            level = newLevel;
            system("cls");
            setColor(LIGHT_YELLOW);
            std::cout << "\n\n      LEVEL UP!\n";
            std::cout << "    Now at level " << level << "!\n";
            std::cout << "    Speed increased!\n";
            Sleep(800);
            setColor(WHITE);
        }
    }
}

void rotatePiece() {
    const auto& originalShape = currentPiece.getShape();
    std::vector<std::vector<bool>> rotated(originalShape[0].size(), 
                                    std::vector<bool>(originalShape.size()));
    for (size_t y = 0; y < originalShape.size(); ++y) {
        for (size_t x = 0; x < originalShape[y].size(); ++x) {
            rotated[x][originalShape.size() - 1 - y] = originalShape[y][x];
        }
    }
    currentPiece.setShape(rotated);
    if (isCollision()) {
        currentPiece.setShape(originalShape);
    }
}

void drawBoard() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
    
    setColor(WHITE);
    std::cout << "Score: " << score << "   Level: " << level << "   Speed: " 
              << std::max(MIN_SPEED, BASE_SPEED - (level-1)*SPEED_DECREMENT) << "ms\n";
    std::cout << "Next Level in: " << LEVEL_SCORE - (score % LEVEL_SCORE) << " points\n";
    
    const auto& currentShape = currentPiece.getShape();
    ConsoleColor currentColor = currentPiece.getColor();
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            bool isCurrent = false;
            for (size_t pieceY = 0; pieceY < currentShape.size(); ++pieceY) {
                for (size_t pieceX = 0; pieceX < currentShape[pieceY].size(); ++pieceX) {
                    if (currentShape[pieceY][pieceX] && 
                        x == currentPiece.getX() + pieceX && 
                        y == currentPiece.getY() + pieceY) {
                        isCurrent = true;
                    }
                }
            }
            
            if (isCurrent) {
                setColor(currentColor);
                std::cout << "[]";
            } else if (board[y][x]) {
                setColor(boardColors[y][x]);
                std::cout << "##";
            } else {
                setColor(BLACK);
                std::cout << "  ";
            }
        }
        setColor(WHITE);
        std::cout << "\n";
    }
    setColor(WHITE);
    std::cout << std::string(BOARD_WIDTH * 2, '-') << "\n";
    std::cout << "Controls: [A]Left [D]Right [W]Rotate [S]Drop [Space]Hard Drop\n";
    std::cout << "          [R]Restart [Q]Quit\n";
}

void resetGame() {
    system("cls");
    board = std::vector<std::vector<bool>>(BOARD_HEIGHT, std::vector<bool>(BOARD_WIDTH, false));
    boardColors = std::vector<std::vector<ConsoleColor>>(BOARD_HEIGHT, std::vector<ConsoleColor>(BOARD_WIDTH, BLACK));
    score = 0;
    level = 1;
    gameOver = false;
    spawnNewPiece();
}

void gameLoop() {
    hideCursor();
    resetGame();
    
    auto lastFallTime = std::chrono::steady_clock::now();
    while (!gameOver) {
        int currentSpeed = std::max(MIN_SPEED, BASE_SPEED - (level-1)*SPEED_DECREMENT);
        
        drawBoard();
        
        if (_kbhit()) {
            char key = _getch();
            switch (tolower(key)) {
                case 'a': 
                    currentPiece.setX(currentPiece.getX() - 1);
                    if (isCollision()) currentPiece.setX(currentPiece.getX() + 1);
                    break;
                case 'd': 
                    currentPiece.setX(currentPiece.getX() + 1);
                    if (isCollision()) currentPiece.setX(currentPiece.getX() - 1);
                    break;
                case 's': 
                    currentPiece.setY(currentPiece.getY() + 1);
                    if (isCollision()) {
                        currentPiece.setY(currentPiece.getY() - 1);
                        mergePieceToBoard();
                        clearLines();
                        spawnNewPiece();
                        if (isCollision()) gameOver = true;
                    }
                    break;
                case 'w': rotatePiece(); break;
                case ' ': 
                    while (!isCollision()) currentPiece.setY(currentPiece.getY() + 1);
                    currentPiece.setY(currentPiece.getY() - 1);
                    mergePieceToBoard();
                    clearLines();
                    spawnNewPiece();
                    if (isCollision()) gameOver = true;
                    break;
                case 'r': resetGame(); break;
                case 'q': gameOver = true; break;
            }
        }
        
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFallTime).count() > currentSpeed) {
            currentPiece.setY(currentPiece.getY() + 1);
            if (isCollision()) {
                currentPiece.setY(currentPiece.getY() - 1);
                mergePieceToBoard();
                clearLines();
                spawnNewPiece();
                if (isCollision()) gameOver = true;
            }
            lastFallTime = currentTime;
        }
        Sleep(30);
    }
    
    showCursor();
    system("cls");
    setColor(LIGHT_RED);
    std::cout << "\n\n  GAME OVER!\n";
    setColor(WHITE);
    std::cout << "  Final Score: " << score << "\n";
    std::cout << "  Final Level: " << level << "\n";
    std::cout << "  Speed Reached: " << std::max(MIN_SPEED, BASE_SPEED - (level-1)*SPEED_DECREMENT) << "ms\n\n";
    std::cout << "  Press R to restart or any other key to quit\n";
    
    if (_getch() == 'r' || _getch() == 'R') {
        gameLoop();
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    gameLoop();
    showCursor();
    return 0;
}
