#ifndef KNOWLEDGE_HPP
#define KNOWLEDGE_HPP

class Sentence;

#include "Sentence.hpp"

class Knowledge{
private:
    std::vector<Sentence> knowledge;

    void remove_tiles_from_knowledge(const Sentence& sentence);
    /**
     * Removes sentence that no longer have Tiles
     */
    void remove_empty_sentences();
    /**
     * True if all Tiles in 'smaller' belong to 'bigger', false otherwise
     */
    bool is_sentenceA_subset_sentenceB(const Sentence& smaller, const Sentence& bigger) const;
    /**
     * Only called when 'smaller' is a subset of 'bigger' and returns the Tiles on 'bigger' that do not belong to smaller.
     * Useful to create the new sentence result from the intersection of 2 sentences
     */
    std::vector<Coordinates> get_unmatched_tiles(const Sentence& smaller, const Sentence& bigger) const;
public:
    void add_sentence(const Sentence& sentence);
    /**
     * Removes the Tile 'coor' from all sentences. If 'ccor' is a bomb, this function is not called, so the num_bombs will be the same in each sentence
     */
    void remove_tile_from_knowledge(const Coordinates& coor);
    /**
     * Applies the inference rules explain to each individual sentence when the num_bombs = 0 or num_bombs = sentence.size()
     * If it is possible to apply the inference rule, then that sentence no longer needs to be stored as the AI knows that those tiles are either safe or bombs
     */
    void apply_inference_rules(Minesweeper& minesweeper);
    /**
     * We keep the sentences that don't match and if A is a subset of B, then:
     *      - Keep A, remove B and add a new one (B - A where the number of bombs is num_bombs in B - num_bombs in A)
     */
    void intersection_inference_rule();
    void show_current_knowledge() const;
};

#endif