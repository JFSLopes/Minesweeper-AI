#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

class AI;
struct Coordinates;

#include <vector>
#include <fstream>
#include "AI.hpp"

enum Tile_Info {NO_BOMB, BOMB, MAYBE, NO_CLUE};
enum Game_State {LOST, WON, PLAYING};

struct Tile{
    int num; // Number of bombs that are close
    Tile_Info info; // Allow the AI to keep track of what it knows about that tile
    bool show; // True if the tile was selected and false otherwise
};

class Minesweeper{
private:
    int board_size;
    std::vector<std::vector<Tile>> board;
    /**
     * This function checks how many bombs are close to the current tile
     */
    int num_close_bombs(int line, int col);
public:
    Minesweeper(std::ifstream& file);

    int get_board_size() const;
    const std::vector<std::vector<Tile>>& get_board() const;
    Game_State game_state() const;
    /**
     * This function will update all tile info after knowing how the board looks like. In reality only updates the number of bombs close
     */
    void update_tile_info();
    bool play(const Coordinates& coor);
    /**
     * If return {-1, -1} then all close tiles were already played
     */
    Coordinates get_close_tile_not_played(int line, int col) const;
    void show_board() const;
};

#endif