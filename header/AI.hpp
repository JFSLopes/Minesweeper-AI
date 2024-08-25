#ifndef AI_HPP
#define AI_HPP

class Minesweeper;

#include "Minesweeper.hpp"

struct Coordinates{
    int x;
    int y;
};

class AI{
private:
    int board_size;
    bool first_play;

    /**
     * Checks if the coordinate is not {-1, -1};
     */
    bool is_coor_valid(const Coordinates& coor) const;
public:
    AI();
    void set_board_size(int board_size);
    Coordinates play(const Minesweeper& minesweeper);
    Coordinates get_random_tile() const;
    Coordinates find_best_play(const Minesweeper& minesweeper) const;

    /**
     * This function looks for played Tiles with 0 bombs near and returns one of the near Tiles that was not yet played
     */
    Coordinates play_safe_tiles(const Minesweeper& minesweeper) const;
};

#endif