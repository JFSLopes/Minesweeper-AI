#include "../header/Knowledge.hpp"
#include <iostream>
#include <set>

void Knowledge::add_sentence(const Sentence& sentence){
    knowledge.push_back(sentence);
}

void Knowledge::remove_empty_sentences(){
    std::vector<Sentence> new_knowledge;
    for (const Sentence& sentence : knowledge){
        if (sentence.get_sentence().empty()) new_knowledge.push_back(sentence);
    }
    knowledge = new_knowledge;
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
    // First simplify the Knowledge
    intersection_inference_rule();

    std::vector<Sentence> new_knowledge;
    std::vector<Sentence> removed_knowledge;
    // Apply the inference rules for when the num_bombs is 0 or num_bombs = sentence.size()
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

void Knowledge::intersection_inference_rule(){
    std::vector<Sentence> new_knowledge;
    // Add the sentences that result from the unmatched Tiles
    std::set<int> s; // Stores the indexes of Sentence that belong to a match
    for (int i = 0; i < (int) knowledge.size(); i++){
        for (int k = i + 1; k < (int) knowledge.size(); k++){
            if (knowledge[i].get_sentence().size() < knowledge[k].get_sentence().size()){
                if (is_sentenceA_subset_sentenceB(knowledge[i], knowledge[k])){

                    std::vector<Coordinates> unmatched_tiles = get_unmatched_tiles(knowledge[i], knowledge[k]);

                    Sentence new_sentence;
                    new_sentence.add_tiles(unmatched_tiles);
                    new_sentence.set_num_bombs(knowledge[k].get_num_bombs() - knowledge[i].get_num_bombs());
                    new_knowledge.push_back(new_sentence);

                    s.insert(k);
                }
            } else {
                if (is_sentenceA_subset_sentenceB(knowledge[k], knowledge[i])){

                    std::vector<Coordinates> unmatched_tiles = get_unmatched_tiles(knowledge[k], knowledge[i]);

                    Sentence new_sentence;
                    new_sentence.add_tiles(unmatched_tiles);
                    new_sentence.set_num_bombs(knowledge[i].get_num_bombs() - knowledge[k].get_num_bombs());
                    new_knowledge.push_back(new_sentence);

                    s.insert(i);
                }
            }
        }
    }

    // Add the sentence that was the subset
    for (int i = 0; i < (int) knowledge.size(); i++){
        if (s.find(i) == s.end()) {
            new_knowledge.push_back(knowledge[i]);
        }
    }
    knowledge = new_knowledge;
}

void Knowledge::show_current_knowledge() const{
    for (const Sentence& s : knowledge){
        for (const Coordinates& c : s.get_sentence()){
            std::cout << "{" << c.x << ", " << c.y << "}" << "  ";
        }
        std::cout << " -> " << s.get_num_bombs() << "\n\n";
    }
}

/*
void Knowledge::intersection_inference_rule(Minesweeper& minesweeper){
    std::vector<Sentence> new_knowledge;
    for (int i = 0; i < (int) knowledge.size(); i++){
        for (int k = i + 1; k < (int) knowledge.size(); k++){
            if (knowledge[i].get_sentence().size() < knowledge[k].get_sentence().size()){ // The first parameter must be the smallest one
                bool is_subset = is_sentenceA_subset_sentenceB(knowledge[i], knowledge[k]);
                if (is_subset){
                    std::vector<Coordinates> unmatched_tiles = get_unmatched_tiles(knowledge[i], knowledge[k]);
                    Sentence new_sentence;
                    new_sentence.add_tiles(unmatched_tiles);
                    new_sentence.set_num_bombs(knowledge[k].get_num_bombs() - knowledge[i].get_num_bombs());
                    new_knowledge.push_back(new_sentence);
                }
            } else {
                bool is_subset = is_sentenceA_subset_sentenceB(knowledge[k], knowledge[i]);
                if (is_subset){
                    std::vector<Coordinates> unmatched_tiles = get_unmatched_tiles(knowledge[k], knowledge[i]);
                    Sentence new_sentence;
                    new_sentence.add_tiles(unmatched_tiles);
                    new_sentence.set_num_bombs(knowledge[i].get_num_bombs() - knowledge[k].get_num_bombs());
                    new_knowledge.push_back(new_sentence);
                }
            }
        }
    }
    // Remove the Tiles that are doing nothing
    std::vector<Sentence> ans;
    for (const Sentence& s1 : knowledge){
        bool match = false;
        for (const Sentence& s2 : new_knowledge){
            if (is_sentenceA_subset_sentenceB(s2, s1)) match = true;
        }

        if (!match) {
            ans.push_back(s1);
        }
    }

    for (const Sentence& s : new_knowledge){
        ans.push_back(s);
    }
    knowledge = ans;
}
*/