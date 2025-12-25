#include <iostream>
#include "minesweeper.h"

Game::Game(int w, int h, int mines) : board(w, h), total_mines(mines){
    board.generateMines(mines);
}

void Game::reveal(int x, int y){
    if(gameover || gamewon || !board.is_valid(x, y)){
        return;
    }
    ICell& cell = board(x, y);
    
    if(cell.CheckFlag()){
        return;
    }

    cell.reveal_on(*this, x, y); // полиморфный вызов, для каждого класса вызовется свой оператор
}

void Game::reveal_area(int x, int y){
    for(int dy = -1; dy <= 1; ++dy){
        for(int dx = -1; dx <= 1; dx++){
            int nx = x + dx;
            int ny = y + dy;
            if(board.is_valid(nx, ny)){ // если точка находится в поле
                ICell& cell = board(nx, ny);
                    if(!cell.isMine() && !cell.CheckOpen() && !cell.CheckFlag()){
                        cell.reveal_on(*this, nx, ny);
                    }
            }
        }
    }
}

void Game::toggle_flag(int x, int y){
    if(gameover || gamewon || !board.is_valid(x, y)){
        return;
    }

    ICell& cell = board(x, y);
    if(!cell.CheckOpen()){

        bool hadFlagBefore = cell.CheckFlag();
        cell.toggleFlag();
        
        if(hadFlagBefore) {
            flag_place--;
        } else {
            flag_place++;
        }
        
        check_win();
    }
}

void Game::check_win(){
    int cur_flags = 0;
    int opened_safe = 0;

    for(int y = 0; y < board.getHeight(); ++y){
        for(int x = 0; x < board.getWidth(); ++x){
            const ICell& cell = board(x, y);
            if(cell.isMine() && cell.CheckFlag()){
                cur_flags++;
            }
            if(!cell.isMine() && cell.CheckOpen()){
                opened_safe++;
            }
        }
    }

    if(cur_flags == total_mines && opened_safe == (board.getHeight() * board.getWidth() - total_mines)){
        gamewon = true;
        std::cout << "Victory! All mines are defused!" << std::endl;
    }
}

void Game::set_game_over(){
    gameover = true;
    board.revealmines();
    std::cout << "The loss! You've hit a landmine!" << std::endl;
}

void Game::print(){
    std::cout << std::endl;
    std::cout << "  ";
    for(int x = 0; x < board.getWidth(); ++x){
        std::cout << " " << x << " ";
    }
    std::cout << std::endl;
    for(int y = 0; y < board.getHeight(); ++y){
        std::cout << y << " ";
        for(int x = 0; x < board.getWidth(); ++x){
            std::cout << board(x, y).getDisplay();
        }
        std::cout << std::endl;
    }
    std::cout << "Flags: " << flag_place << "/" << total_mines;
    std::cout << " | ";
    if(gameover){
        std::cout << "Loss( Bro, you need to train";
    } else if(gamewon){
        std::cout << "Victory";
    } else{
        std::cout << "Play";
    }
    std::cout << std::endl;

}
