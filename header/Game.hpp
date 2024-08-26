#ifndef GAME_HPP
#define GAME_HPP

#include "Minesweeper.hpp"
#include "AI.hpp"
#include <fstream>

class Game{
private:
    Minesweeper minesweeper;
    AI ai;
    bool show_current_knowledge;
public:
    Game(std::ifstream& file, bool show_current_knowledge);
    void run();
};

#endif