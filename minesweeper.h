#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <random>

class ICell {
protected:
    bool isOpen = false;
    bool isFlagged = false;

public:
    virtual ~ICell() = default;

    virtual bool isMine() const = 0;
    virtual std::string getDisplay() const = 0;

    void open() { isOpen = true; }
    void toggleFlag() { isFlagged = !isFlagged; }

    bool CheckOpen() const { return isOpen; }
    bool CheckFlag() const { return isFlagged; }
};

class MineCell : public ICell {
public:
    bool isMine() const override { return true; }

    std::string getDisplay() const override {
        if (isOpen) return "[*]"; // Мина
        if (isFlagged) return "[F]";
        return "[ ]";
    }
};

class SafeCell : public ICell {
    int neighbors = 0;
public:
    void setNeighbors(int n) { neighbors = n; }

    bool isMine() const override { return false; }

    std::string getDisplay() const override {
        if (isFlagged) return "[F]";
        if (!isOpen) return "[ ]";
        if (neighbors == 0) return " . ";
        return " " + std::to_string(neighbors) + " ";
    }
};

class Board {
private:
    int width, height;
    std::vector<std::vector<std::unique_ptr<ICell>>> grid;

public:
    Board(int w, int h);
    void generateMines(int count);

    ICell& operator()(int x, int y) {
        return *grid[y][x];
    }

    const ICell& operator()(int x, int y) const {
        return *grid[y][x];
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
};

#endif