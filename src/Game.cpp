#include "../header/Game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

Game::Game(std::ifstream& file) : minesweeper(Minesweeper(file)) {
    ai.set_board_size(minesweeper.get_board_size());
    }

void Game::run(){
    while(true){
        Coordinates coor = ai.play(minesweeper);
        minesweeper.play(coor);
        minesweeper.show_board();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));

        switch (minesweeper.game_state()){
            case WON:
                std::cout << "The AI WON\n";
                return;
            case LOST:
                std::cout << "The AI LOST\n";
                return;
            case PLAYING:
                break;
        }
    }
}