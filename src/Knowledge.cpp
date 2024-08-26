#include "../header/Knowledge.hpp"

void Knowledge::add_sentence(const Sentence& sentence){
    knowledge.push_back(sentence);
}

void Knowledge::apply_inference_rules(Minesweeper& minesweeper){
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