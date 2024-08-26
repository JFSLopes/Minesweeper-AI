#include "../header/Sentence.hpp"

const std::vector<Coordinates>& Sentence::get_sentence() const{
    return sentence;
}

int Sentence::get_num_bombs() const{
    return num_bombs;
}

void Sentence::add_tiles(const std::vector<Coordinates>& coors){
    sentence = coors;
}

void Sentence::set_num_bombs(int num_bombs){
    this->num_bombs = num_bombs;
}

bool Sentence::use_inference_rules(Minesweeper& minesweeper) const{
    std::vector<std::vector<Tile>> board = minesweeper.get_board();
    if (num_bombs == 0 or (num_bombs == (int) sentence.size())){
        Tile_Info new_info = (num_bombs == 0 ? NO_BOMB : BOMB);
        for (const Coordinates& coor : sentence){
            minesweeper.update_tile_info(coor.x, coor.y, new_info);
        }
        return true;
    }
    return false;
}

void Sentence::remove_tile(const Coordinates& coor, bool decrease_num_bombs){
    for (auto itr = sentence.begin(); itr != sentence.end(); itr++){
        if (itr->x == coor.x and itr->y == coor.y){
            sentence.erase(itr);
            if (decrease_num_bombs) num_bombs--;
            return;
        }
    }
}