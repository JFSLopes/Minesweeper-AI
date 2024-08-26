#include "../header/AI.hpp"

AI::AI() : first_play(true), knowledge(std::make_unique<Knowledge>()){}

void AI::set_board_size(int board_size){
    this->board_size = board_size;
}

bool AI::is_coor_valid(const Coordinates& coor) const{
    return (coor.x != -1 and coor.y != -1);
}

Coordinates AI::play(Minesweeper& minesweeper){
    Coordinates coor;
    if (first_play){
        first_play = false;
        coor = get_random_tile(minesweeper);
    } else {
        coor = find_best_play(minesweeper);
    }
    // Update the board with the new play
    minesweeper.update_close_tiles_info(coor.x, coor.y);
    Tile tile = minesweeper.get_tile(coor.x, coor.y);

    // Update current knowledge if it is not a bomb
    if (tile.num != -1) update_knowledge(tile.num, coor.x, coor.y, minesweeper);
    return coor;
}

Coordinates AI::get_random_tile(Minesweeper& minesweeper) const{
    while (true){
        int x = rand() % board_size;
        int y = rand() % board_size;

        const Tile tile = minesweeper.get_tile(x, y);
        if (!tile.show and tile.info != BOMB) return {x, y};
    }
    return {-1, -1};
}

Coordinates AI::get_tile_maybe_bomb(Minesweeper& minesweeper) const{
    std::vector<std::vector<Tile>> board = minesweeper.get_board();
    std::vector<Coordinates> tiles_maybe_bomb;

    for (int x = 0; x < board_size; x++){
        for (int y = 0; y < board_size; y++){
            if (!board[x][y].show and board[x][y].info == MAYBE){
                tiles_maybe_bomb.push_back({x, y});
            }
        }
    }

    if (tiles_maybe_bomb.empty()) return {-1, -1};

    int random = rand() % tiles_maybe_bomb.size();
    return tiles_maybe_bomb[random];
}

Coordinates AI::find_best_play(Minesweeper& minesweeper) const{
    Coordinates coor = get_safe_tile(minesweeper);
    if (is_coor_valid(coor)) return coor;

    coor = get_tile_maybe_bomb(minesweeper);
    if (is_coor_valid(coor)) return coor;

    return get_random_tile(minesweeper);
}

Coordinates AI::get_safe_tile(Minesweeper& minesweeper) const{
    std::vector<std::vector<Tile>> board = minesweeper.get_board();
    for (int x = 0; x < board_size; x++){
        for (int y = 0; y < board_size; y++){
            if (!board[x][y].show and board[x][y].info == NO_BOMB){
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

void AI::update_knowledge(int num_bombs, int line, int col, Minesweeper& minesweeper){
    // Remove the played tile from the knowledge
    knowledge->remove_tile_from_knowledge({line, col});

    std::vector<Coordinates> tiles = minesweeper.get_close_tiles_not_selected(line, col, num_bombs);

    Sentence new_sentence;
    new_sentence.add_tiles(tiles);
    new_sentence.set_num_bombs(num_bombs);
    
    knowledge->add_sentence(new_sentence);
    knowledge->apply_inference_rules(minesweeper);    
}

void AI::show_current_knowledge() const{
    knowledge->show_current_knowledge();
}