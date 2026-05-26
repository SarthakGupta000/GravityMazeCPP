#include <iostream>

class Vec2 {
    public:
    int x;
    int y;

    Vec2(int valx, int valy) : x(valx), y(valy) {}
};

Vec2 getPlayerInput();

// 0 if valid
// 1 if not
int checkIfInvalid(int x, int y, int height, int width);

void printBoard(char **grid, int height, int width);

// prioritizes player movement over gravity
Vec2 handleMovement(Vec2 playerInput, char **grid, int height, int width);

void runGame(char **grid, int height, int width);