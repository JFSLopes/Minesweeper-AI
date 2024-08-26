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
    /**
     * Returns a random Tile that is not marked 'BOMB'
     */
    Coordinates get_random_tile(Minesweeper& minesweeper) const;
    /**
     * Returns the coordinates of a Tile marked by the AI as 'MAYBE'
     */
    Coordinates get_tile_maybe_bomb(Minesweeper& minesweeper) const;
    /**
     * This function works by:
     *      1. Looking for Tiles marked as 'NO_BOMB'
     *      2. Looking for Tiles marked as 'MAYBE'
     *      3. Chooses a random Tile that is not marked 'BOMB'
     */
    Coordinates find_best_play(Minesweeper& minesweeper) const;

    /**
     * This function looks for Tiles not yet played but which the AI marked 'NO_BOMB'.
     */
    Coordinates get_safe_tile(Minesweeper& minesweeper) const;
    /**
     * This function removes the Tile {line, col} from all the current known sentences, then creates a new sentence with the new information from the Tile
     * and then applies the inferences rules
     */
    void update_knowledge(int num_bombs, int line, int col, Minesweeper& minesweeper);

    void show_current_knowledge() const;

};

#endif