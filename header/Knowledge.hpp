#ifndef KNOWLEDGE_HPP
#define KNOWLEDGE_HPP

class Sentence;

#include "Sentence.hpp"

class Knowledge{
private:
    //std::vector<Sentence> knowledge;

    void remove_tiles_from_knowledge(const Sentence& sentence);
public:
    std::vector<Sentence> knowledge;
    void add_sentence(const Sentence& sentence);
    /**
     * Even if the tile is a bomb, the AI will lose, so no point in check that
     */
    void remove_tile_from_knowledge(const Coordinates& coor);
    void apply_inference_rules(Minesweeper& minesweeper);

    void intersection_inference_rule(Minesweeper& minesweeper);
};

#endif