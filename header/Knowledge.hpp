#ifndef KNOWLEDGE_HPP
#define KNOWLEDGE_HPP

class Sentence;

#include "Sentence.hpp"

class Knowledge{
private:
    std::vector<Sentence> knowledge;

    void remove_tiles_from_knowledge(const Sentence& sentence);
    void remove_empty_sentences();
    bool is_sentenceA_subset_sentenceB(const Sentence& smaller, const Sentence& bigger) const;
    std::vector<Coordinates> get_unmatched_tiles(const Sentence& smaller, const Sentence& bigger) const;
public:
    void add_sentence(const Sentence& sentence);
    /**
     * Even if the tile is a bomb, the AI will lose, so no point in check that
     */
    void remove_tile_from_knowledge(const Coordinates& coor);
    void apply_inference_rules(Minesweeper& minesweeper);
    /**
     * If A is a subset of B, then we create two Sentences:
     *      - Keep A and remove B
     *      - Add a new one: B - A where the number of bombs is num_bombs in B - num_bombs in A
     */
    void intersection_inference_rule();
    void show_current_knowledge() const;
};

#endif