# Minesweeper AI Game

This repository contains a Minesweeper game where an AI plays based on a board representation provided by the user. The user inputs a file with the board setup, and the AI makes decisions to reveal tiles, avoid bombs, and attempt to clear the board.

## Board Symbols

The game board uses the following symbols:

- **Green 'X'**: The AI is certain this tile contains a bomb.
- **Red 'X'**: The AI mistakenly chose a tile containing a bomb, which it thought was safe.
- **Blue 'S'**: Tiles that the AI has determined are safe but have not yet been revealed.
- **White number**: The number of bombs adjacent to this tile.
- **Empty space**: Tiles that are still unrevealed, which the AI does not yet have enough information to classify as either 'safe' or 'bomb'.


## Important Notation (Knowledge Representation)

- **Sentence**: Represents the AI's knowledge about specific tiles and the number of bombs among them. A Sentence stores a set of tiles and the count of bombs within those tiles. For example, `{{1, 2}, {1, 3}, {1, 4}} -> 2` means that out of the tiles `{1, 2}`, `{1, 3}`, and `{1, 4}`, exactly two of them are bombs.

- **Knowledge**: Refers to all the information the AI has accumulated at any given state of the game. It consists of all the Sentences the AI has derived up to that point. This knowledge base is updated as the game progresses and new Sentences are inferred.

## File Structure

The input file should have the `.minesweeper` extension. Here's how it is structured:

- The first line contains the board dimensions (the board is always square).
- 'X' represents bombs, and ' ' (space) represents free tiles.

For example, given a file named [Board](assets/board.minesweeper), it would correspond to a board layout shown in [Example](assets/example.png).

### Tile Structure

Each tile on the board holds the following data:

- **num**: The number of bombs adjacent to this tile.
- **info**: Information the AI uses to track if the tile has a bomb, is safe, or is uncertain.
- **show**: A boolean value indicating whether the AI has chosen this tile, making its information visible when displaying the board.

## How the AI Plays

1. **When a Tile is Played**:
    - The chosen tile is removed from all sentences in which it appeared (Implementation on [`remove_tile_from_knowledge`](src/knowledge.cpp)).
    - A new sentence is created using nearby tiles marked as "MAYBE". The AI does not consider tiles it knows are bombs or safe. For example, if a chosen tile is surrounded by two bombs and neighboring tiles A, B, C, D, and E, and the AI knows A is bomb and B is safe, the sentence created should be {C, D, E} = 1. Implementation on [`update_knowledge`](src/AI.cpp).

2. **Applying Inference Rules**:
    - **Intersection Rule**: If Sentence A contains 'x' bombs and is a subset of Sentence B with 'y' bombs, then the difference (B - A) must contain (y - x) bombs.
    - Other Inference Rules: (Implementation on [`use_inference_rules`](src/Sentence.cpp))
        - "If the number of bombs equals the number of tiles that could be bombs, all those tiles are bombs."
        - "If the number of bombs is 0, none of the tiles in that sentence are bombs."

3. **Tile Selection Strategy**:
    - The AI prioritizes unrevealed tiles marked as 'NO_BOMB'.
    - Next, it considers unrevealed tiles marked as 'MAYBE'.
    - If neither of the above options are available, it picks a random tile to play.
    - Implentation on [`play`](src/AI.cpp)

---

This AI Minesweeper offers an interesting demonstration of logical inference and decision-making in a classic game setting.
