#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

const int ROWS = 20;
const int COLS = 40;

void initializeGrid(std::vector<std::vector<bool>>& grid) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = rand() % 2 == 0;
        }
    }
}

void printGrid(const std::vector<std::vector<bool>>& grid) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << (grid[i][j] ? "O" : " ") << " ";
        }
        std::cout << std::endl;
    }
}

int countAliveNeighbors(const std::vector<std::vector<bool>>& grid, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS && grid[r][c]) {
                ++count;
            }
        }
    }
    return count;
}

void updateGrid(std::vector<std::vector<bool>>& grid) {
    std::vector<std::vector<bool>> newGrid(ROWS, std::vector<bool>(COLS, false));
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int aliveNeighbors = countAliveNeighbors(grid, i, j);
            if (grid[i][j]) {
                newGrid[i][j] = (aliveNeighbors == 2 || aliveNeighbors == 3);
            } else {
                newGrid[i][j] = (aliveNeighbors == 3);
            }
        }
    }
    grid = newGrid;
}

int main() {
    std::vector<std::vector<bool>> grid(ROWS, std::vector<bool>(COLS, false));

    initializeGrid(grid);

    while (true) {
        printGrid(grid);
        updateGrid(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("clear");
    }

    return 0;
}
