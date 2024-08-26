#include "../header/Game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

Game::Game(std::ifstream& file, bool show_current_knowledge) : minesweeper(Minesweeper(file)), show_current_knowledge(show_current_knowledge) {
    ai.set_board_size(minesweeper.get_board_size());
    }

void Game::run(){
    while(true){
        Coordinates coor = ai.play(minesweeper);
        minesweeper.play(coor);
        minesweeper.show_board();
        if (show_current_knowledge) ai.show_current_knowledge();
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        #ifdef _WIN32    
            system("cls");
        #else
            system("clear");
        #endif

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