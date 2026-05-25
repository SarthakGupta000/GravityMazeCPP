#include <iostream>

class Vec2 {
    public:
    int x;
    int y;

    Vec2(int valx, int valy) : x(valx), y(valy) {}
};

Vec2 getPlayerInput() {
    std::cout << "Enter move ((U)p, (D)own, (L)eft, (R)ight) -> ";
    char x; // U, D, L, R
    std::cin >> x;
    Vec2 move(0, 0);
    if (x == 'U') {
        move.y = -1;
    }
    else if (x == 'D') {
        move.y = 1;
    }
    else if (x == 'L') {
        move.x = -1;
    }
    else if (x == 'R') {
        move.x = 1;
    }
    else {
        std::cout << "Invalid move, turn has been skipped" << std::endl;
    }
    return move;
}

// 0 if valid
// 1 if not
int checkIfInvalid(int x, int y, int height, int width) {
    if (y >= height || y <= -1) {
        return 1;
    }
    if (x >= width || x <= -1) {
        return 1;
    }
    return 0;
}

// prioritizes player movement over gravity
Vec2 handleMovement(Vec2 playerInput, char **grid, int height, int width) {
    Vec2 gravity(0, 1);
    int playerY;
    int playerX;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (grid[j][i] == 'S') {
                playerY = j;
                playerX = i;
            }
        }
    }
    Vec2 playerPos(playerX, playerY);
    playerPos.x += playerInput.x;
    playerPos.y += playerInput.y;
    int moveValidity = checkIfInvalid(playerPos.x, playerPos.y, height, width);
    if (moveValidity == 1) {
        std::cout << "Invalid move, turn has been skipped" << std::endl;
        playerPos.x = playerX;
        playerPos.y = playerY;
        return playerPos;
    }
    if (grid[playerPos.y][playerPos.x] == '#' && grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == '#') {
        std::cout << "Invalid move, turn has been skipped" << std::endl;
        playerPos.x = playerX;
        playerPos.y = playerY;
        return playerPos;
    }
    if ((grid[playerPos.y][playerPos.x] == '.' || grid[playerPos.y][playerPos.x] == 'E') && grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == '#') {
        return playerPos;
    }
    if (grid[playerPos.y][playerPos.x] == '#' && (grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == '.' || grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == 'E')) {
        playerPos.x += gravity.x;
        playerPos.y += gravity.y;
        return playerPos;
    }
    playerPos.x += gravity.x;
    playerPos.y += gravity.y;
    return playerPos;
}