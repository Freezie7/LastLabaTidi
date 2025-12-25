#include <iostream>
#include <string>
#include "minesweeper.h"

void process_cell(ICell& cell, Game& game, int x, int y){
    std::cout << "Cell processing" << cell.getDisplay() << std::endl;
    if(!cell.CheckOpen()){
        cell.reveal_on(game, x, y);
    }
}

void process_cell(Game& game, int x, int y, bool use_flag){
    if(use_flag){
        game.toggle_flag(x, y);
    } else {
        ICell& cell = game.get_board()(x, y);
        process_cell(cell, game, x, y);
    }
}

int main(){
    std::cout <<"=======MINESWEEPER======="  << std::endl;
    std::cout << "Commands: " << std::endl;
    std::cout << "r Collumn Row reveal a cell" << std::endl;
    std::cout << "f Column Row place/remove flag" << std::endl;
    std::cout << "q - quit" << std::endl;

    Game game(8, 8, 10);

    while(!game.is_game_over() && !game.is_game_won()){
        game.print();

        std::cout << "Enter command: (word, column, row)" << std::endl;
        std::string cmd;
        std::cin >> cmd;
        if(cmd == "q"){
            break;
        } 
        if(cmd == "r" || cmd == "f"){
            int x, y;
            if(std::cin >> x >> y){
                if(cmd == "r"){
                    process_cell(game, x, y, false);
                } else {
                    game.toggle_flag(x, y);
                }
            } else {
                std::cout << "Invalid coordinates" << std::endl;
                std::cin.clear();
            }
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    game.print();
    std::cout << "Good game, well played" << std::endl;
    std::cout << "Performed by Ivan Zhemchugov and Vlad Kononyuk" << std::endl;
    return 0;

}