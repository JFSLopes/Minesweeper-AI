#ifndef AI_HPP
#define AI_HPP

class Minesweeper;
class Knowledge;

#include "Minesweeper.hpp"
#include "Knowledge.hpp"
#include <memory>

struct Coordinates{
    int x;
    int y;
};

class AI{
private:
    int board_size;
    bool first_play;
    std::unique_ptr<Knowledge> knowledge;
    /**
     * Checks if the coordinate is not {-1, -1};
     */
    bool is_coor_valid(const Coordinates& coor) const;
public:
    AI();
    void set_board_size(int board_size);
    Coordinates play(Minesweeper& minesweeper);
    Coordinates get_random_tile(Minesweeper& minesweeper) const;
    /**
     * Returns the coordinates of a Tile that might have a bomb or {-1, -1}
     */
    Coordinates get_tile_maybe_bomb(Minesweeper& minesweeper) const;
    Coordinates find_best_play(Minesweeper& minesweeper) const;

    /**
     * This function looks for played Tiles with 0 bombs near and returns one of the near Tiles that was not yet played
     */
    Coordinates get_safe_tile(Minesweeper& minesweeper) const;
    void update_knowledge(int num_bombs, int line, int col, Minesweeper& minesweeper);

    void show_current_knowledge() const;

};

#endif