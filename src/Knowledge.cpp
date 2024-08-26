#include "../header/Knowledge.hpp"

void Knowledge::add_sentence(const Sentence& sentence){
    knowledge.push_back(sentence);
}

bool Knowledge::is_sentenceA_subset_sentenceB(const Sentence& smaller, const Sentence& bigger) const{
    for (const Coordinates& coor1 : smaller.get_sentence()){
        bool match = false;
        for (const Coordinates& coor2 : bigger.get_sentence()){
            if (coor1.x == coor2.x and coor1.y == coor2.y) match = true;
        }
        if (!match) return false;
    }
    return true;
}

std::vector<Coordinates> Knowledge::get_unmatched_tiles(const Sentence& smaller, const Sentence& bigger) const{
    std::vector<Coordinates> ans;
    for (const Coordinates& coor1 : bigger.get_sentence()){
        bool match = false;
        for (const Coordinates& coor2 : smaller.get_sentence()){
            if (coor1.x == coor2.x and coor1.y == coor2.y) match = true;
        }
        if (!match) ans.push_back(coor1);
    }
    return ans;
}

void Knowledge::apply_inference_rules(Minesweeper& minesweeper){
    intersection_inference_rule(minesweeper);
    std::vector<Sentence> new_knowledge;
    std::vector<Sentence> removed_knowledge;
    for (const Sentence& sentence : knowledge){
        if (!sentence.use_inference_rules(minesweeper)){ // If the inference rules were not applied, then the sentence is still valid
            new_knowledge.push_back(sentence);
        } else {
            removed_knowledge.push_back(sentence);
        }
    }
    knowledge = new_knowledge;

    // Deleate all Tiles the AI knows are BOMB or NO_BOMB from the knowledge
    for (const Sentence& sentence : removed_knowledge){
        remove_tiles_from_knowledge(sentence);
    }
}

void Knowledge::remove_tiles_from_knowledge(const Sentence& sentence){
    bool are_tiles_bomb = (int) sentence.get_sentence().size() == sentence.get_num_bombs() ? true : false;
    for (const Coordinates& coor : sentence.get_sentence()){
        for (Sentence& s : knowledge){
            s.remove_tile(coor, are_tiles_bomb);
        }
    }
}

void Knowledge::remove_tile_from_knowledge(const Coordinates& coor){
    for (Sentence& s : knowledge){
        s.remove_tile(coor, false);
    }
}

void Knowledge::intersection_inference_rule(Minesweeper& minesweeper){
    for (int i = 0; i < (int) knowledge.size(); i++){
        for (int k = i + 1; k < (int) knowledge.size(); k++){
            if (knowledge[i].get_sentence().size() < knowledge[k].get_sentence().size()){ // The first parameter must be the smallest one
                bool is_subset = is_sentenceA_subset_sentenceB(knowledge[i], knowledge[k]);
                if (is_subset){
                    std::vector<Coordinates> safe_tiles = get_unmatched_tiles(knowledge[i], knowledge[k]);
                    for (Coordinates& coor : safe_tiles){
                        minesweeper.update_tile_info(coor.x, coor.y, NO_BOMB);
                        remove_tile_from_knowledge(coor);
                    }
                }
            } else {
                bool is_subset = is_sentenceA_subset_sentenceB(knowledge[k], knowledge[i]);
                if (is_subset){
                    std::vector<Coordinates> safe_tiles = get_unmatched_tiles(knowledge[k], knowledge[i]);
                    for (Coordinates& coor : safe_tiles){
                        minesweeper.update_tile_info(coor.x, coor.y, NO_BOMB);
                        remove_tile_from_knowledge(coor);
                    }
                }
            }
        }
    }
}