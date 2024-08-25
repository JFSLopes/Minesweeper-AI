#ifndef GAME_HPP
#define GAME_HPP

#include "Minesweeper.hpp"
#include "AI.hpp"
#include <fstream>

class Game{
private:
    Minesweeper minesweeper;
    AI ai;
public:
    Game(std::ifstream& file);
    void run();
};

#endif