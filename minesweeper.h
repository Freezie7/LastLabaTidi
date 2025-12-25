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

    virtual void reveal_on(class Game& game, int x, int y) = 0; //+
};

class MineCell : public ICell {
public:
    bool isMine() const override { return true; }

    std::string getDisplay() const override {
        if (isOpen) return "[*]"; // Мина
        if (isFlagged) return "[F]";
        return "[ ]";
    }
    void reveal_on(Game& game, int x, int y) override;
};

class SafeCell : public ICell {
    int neighbors = 0;
public:
    void setNeighbors(int n) { neighbors = n; }
    int getNeighbors() {return neighbors; } //

    bool isMine() const override { return false; }

    std::string getDisplay() const override {
        if (isFlagged) return "[F]";
        if (!isOpen) return "[ ]";
        if (neighbors == 0) return " . ";
        return " " + std::to_string(neighbors) + " ";
    }

    void reveal_on(Game& game, int x, int y) override; //+
};

class Board {
private:
    int width, height;
    std::vector<std::vector<std::unique_ptr<ICell>>> grid;

public:
    Board(int w, int h); //+
    void generateMines(int count); //+

    bool is_valid(int x, int y) const; //+

    ICell& operator()(int x, int y); //+

    const ICell& operator()(int x, int y) const; //+

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    void revealmines(); // если проигрыш
};

class Game{ // 
private: 

    Board board;
    int total_mines; 
    int flag_place = 0;
    bool gameover = false;
    bool gamewon = false;
protected:
public:
    Game(int w, int h, int mines); //+
    Board& get_board() {return board; }

    void reveal(int x, int y); //открытие +
    void toggle_flag(int x, int y); //постановка или убирание флага
    void print();

    void reveal_area(int x, int y); //+
    void check_win(); //+
    void set_game_over(); //+

    bool is_game_over() {return gameover;};
    bool is_game_won() {return gamewon;};
    int get_total_mines();
};

#endif