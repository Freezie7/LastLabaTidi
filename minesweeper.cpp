#include "minesweeper.h"
#include <ctime>

Board::Board(int w, int h) : width(w), height(h) {
    grid.resize(height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // пустые клетки
            grid[y].push_back(std::make_unique<SafeCell>());
        }
    }
}

void Board::generateMines(int count) {
    std::srand(std::time(nullptr));
    int placed = 0;
    
    while (placed < count) {
        int x = std::rand() % width;
        int y = std::rand() % height;

        if (!grid[y][x]->isMine()) {
            // ЗАМЕНЯЕМ SafeCell на MineCell
            grid[y][x] = std::make_unique<MineCell>();
            placed++;
        }
    }


    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {ы
            if (grid[y][x]->isMine()) continue;

            int minesAround = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int ny = y + dy;
                    int nx = x + dx;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        if (grid[ny][nx]->isMine()) minesAround++;
                    }
                }
            }
            if (SafeCell* safe = dynamic_cast<SafeCell*>(grid[y][x].get())) {
                safe->setNeighbors(minesAround);
            }
        }
    }
}