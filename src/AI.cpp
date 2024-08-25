#include "../header/AI.hpp"

AI::AI() : first_play(true) {}

void AI::set_board_size(int board_size){
    this->board_size = board_size;
}

bool AI::is_coor_valid(const Coordinates& coor) const{
    return (coor.x != -1 and coor.y != -1);
}

Coordinates AI::play(const Minesweeper& minesweeper){
    if (first_play){
        first_play = false;
        return get_random_tile();
    } else {
        return find_best_play(minesweeper);
    }
}

Coordinates AI::get_random_tile() const{
    int x = rand() % board_size;
    int y = rand() % board_size;
    return {x, y};
}

Coordinates AI::find_best_play(const Minesweeper& minesweeper) const{
    Coordinates coor = play_safe_tiles(minesweeper);
    if (is_coor_valid(coor)) return coor;
    return get_random_tile();
}

Coordinates AI::play_safe_tiles(const Minesweeper& minesweeper) const{
    std::vector<std::vector<Tile>> board = minesweeper.get_board();
    for (int x = 0; x < board_size; x++){
        for (int y = 0; y < board_size; y++){
            if (board[x][y].show and (board[x][y].num == 0)){
                Coordinates coor = minesweeper.get_close_tile_not_played(x, y);
                if (is_coor_valid(coor)) {
                    return {coor.x, coor.y};
                }
            }
        }
    }
    return {-1, -1};
}