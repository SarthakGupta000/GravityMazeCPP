#include "util.hpp"

int main() { // for testing
    char **grid = new char*[10];
    for (int i = 0; i < 10; i++) {
        grid[i] = new char[10];
    }
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            grid[y][x] = '.';
        }
    }
    // S . . . . . . . . . 
    // # # # # . # # # # # 
    // . . . . . . . . . . 
    // . . . . . . . . . . 
    // . # # # # # # # # # 
    // . . . . . . . . . . 
    // . . . . . . . . . . 
    // . . . . . . . . . . 
    // . . . . . . . . . . 
    // . . . . . . . . . E 
    for (int i = 0; i < 10; i++) {
        grid[1][i] = '#';
        grid[4][i] = '#';
    }
    grid[1][4] = '.';
    grid[4][0] = '.';
    grid[0][0] = 'S';
    grid[9][9] = 'E';
    runGame(grid, 10, 10);
    for (int i = 0; i < 10; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}