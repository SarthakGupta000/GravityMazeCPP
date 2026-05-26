#include <iostream>
#include "util.hpp"

class Vec2;

Vec2 getPlayerInput() {
    std::cout << "Press Ctrl + C to quit!";
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

void printBoard(char **grid, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << grid[y][x] << ' ';
        }
        std::cout << std::endl;
    }
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
    int playerY; // if everything works well, player will be there
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
    if (moveValidity == 1) { // discard if player moved wrong
        std::cout << "Invalid move, turn has been skipped" << std::endl;
        playerPos.x = playerX;
        playerPos.y = playerY;
        return Vec2(playerPos.x - playerX, playerPos.y - playerY);
    }
    moveValidity = checkIfInvalid(playerPos.x + gravity.x, playerPos.y + gravity.y, height, width);
    if (moveValidity == 1) {
        if (grid[playerPos.y][playerPos.x] == '#') {
            std::cout << "Invalid move, turn has been skipped" << std::endl;
            playerPos.x = playerX;
            playerPos.y = playerY;
            return Vec2(playerPos.x - playerX, playerPos.y - playerY);
        }
        if (grid[playerPos.y][playerPos.x] == '.' || grid[playerPos.y][playerPos.x] == 'E') { // keep player only if gravity moved wrong
            return Vec2(playerPos.x - playerX, playerPos.y - playerY);
        }
    }
    if (grid[playerPos.y][playerPos.x] == '#' && grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == '#') { // discard if player and gravity both move into a wall
        std::cout << "Invalid move, turn has been skipped" << std::endl;
        playerPos.x = playerX;
        playerPos.y = playerY;
        return Vec2(playerPos.x - playerX, playerPos.y - playerY);
    }
    if ((grid[playerPos.y][playerPos.x] == '.' || grid[playerPos.y][playerPos.x] == 'E') && grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == '#') {
        return Vec2(playerPos.x - playerX, playerPos.y - playerY);
    }
    if (grid[playerPos.y][playerPos.x] == '#' && (grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == '.' || grid[playerPos.y + gravity.y][playerPos.x + gravity.x] == 'E')) {
        playerPos.x += gravity.x;
        playerPos.y += gravity.y;
        return Vec2(playerPos.x - playerX, playerPos.y - playerY);
    }
    playerPos.x += gravity.x;
    playerPos.y += gravity.y;
    return Vec2(playerPos.x - playerX, playerPos.y - playerY);
}

void runGame(char **grid, int height, int width) {
    while (1) {
        printBoard(grid, height, width);
        Vec2 player_move = getPlayerInput();
        Vec2 final_move = handleMovement(player_move, grid, height, width);
        int y;
        int x;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                if (grid[j][i] == 'S') {
                    y = j;
                    x = i;
                }
            }
        }
        y += final_move.y;
        x += final_move.x;
        if (grid[y][x] == 'E') {
            std::cout << "Good job! You won!";
            break;
        }
        grid[y - final_move.y][x - final_move.x] = '.';
        grid[y][x] = 'S';
    }
}