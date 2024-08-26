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
    /**
     * @param num_bombs Indicates the number of close bombs. This is useful in to verify if the all the close bombs are already known. The function will change it
     * to the number of bombs left to find
     */
    std::vector<Coordinates> get_close_tiles_not_selected(int line, int col, int& num_bombs) const;
    const Tile& get_tile(int line, int col) const;
    Game_State game_state() const;
    /**
     * This function will update all tile info after knowing how the board looks like. In reality only updates the number of bombs close
     */
    void update_tile_info(int line, int col, Tile_Info info);
    void update_tile_info();
    void update_close_tiles_info(int line, int col);
    bool play(const Coordinates& coor);
    /**
     * Used when a Tile with 0 close bombs is found, because we know all close tiles will be safe
     */
    void mark_close_tiles_safe(int line, int col);
    void mark_close_tiles_maybe(int line, int col);
    void show_board() const;
};

#endif