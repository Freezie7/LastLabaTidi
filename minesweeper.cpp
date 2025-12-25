#include "minesweeper.h"
#include <ctime>



void MineCell::reveal_on(Game& game, int x, int y){
    open();
    game.set_game_over(); // проигрыш
}

void SafeCell::reveal_on(Game& game, int x, int y){
    if(CheckOpen() || CheckFlag()){
        return;
    }
    open();

    if(getNeighbors() == 0){ //открытие соседей
        game.reveal_area(x, y);
    }

    game.check_win();
}
