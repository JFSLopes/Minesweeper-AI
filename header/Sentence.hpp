#ifndef SENTENCE_HPP
#define SENTENCE_HPP

struct Coordinates;
class AI;

#include "AI.hpp"
#include <vector>

class Sentence{
private:
    std::vector<Coordinates> sentence; // Stores the tiles that the AI know might have bombs
    int num_bombs; // Number of bombs on the Tiles in 'sentence'
public:
    const std::vector<Coordinates>& get_sentence() const;
    int get_num_bombs() const;

    void add_tiles(const std::vector<Coordinates>& coor);
    void set_num_bombs(int num_bombs);
    /**
     * If the num_bombs = 0, then all Tiles in 'sentence' are safe
     * If the num_bombs = sentence.size(), then all Tiles are bombs
     * 
     * If returns true, then one of the inference rules was applied which means the sentence can be erased
     */
    bool use_inference_rules(Minesweeper& minesweeper) const;
    /**
     * 
     * @param decresase_num_bombs If true means that the Tile 'coor' is a bomb, so if the sentence has 'coor', then we remove 'coor' and decrase the num_bombs
     */
    void remove_tile(const Coordinates& coor, bool decrease_num_bombs);
};

#endif