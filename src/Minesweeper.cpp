#include "../header/Minesweeper.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

Minesweeper::Minesweeper(std::ifstream& file){
    std::string line;
    // Get board dimensions
    std::getline(file, line);
    board_size = (int) std::stoi(line);

    // Create the board array with the correct dimensions
    board = std::vector(board_size, std::vector<Tile>(board_size));

    int curr_line = 0;
    // Read board
    while (std::getline(file, line)){
        for (int i = 0; i < board_size; i++){
            // If is a bomb, 'num' will be -1 otherwise 0
            int is_bomb = (line[i] == 'X' ? -1 : 0);
            board[curr_line][i] = {is_bomb, NO_CLUE, false};
        }
        curr_line++;
    }
    // After building the board, an tile update is run
    update_tile_info();
}

int Minesweeper::get_board_size() const{
    return board_size;
}

const std::vector<std::vector<Tile>>& Minesweeper::get_board() const{
    return board;
}

const Tile& Minesweeper::get_tile(int line, int col) const{
    return board[line][col];
}

void Minesweeper::update_tile_info(int line, int col, Tile_Info info){
    board[line][col].info = info;
}

std::vector<Coordinates> Minesweeper::get_close_tiles_not_selected(int line, int col, int& num_bombs) const{
    std::vector<Coordinates> ans;
    int bombs = 0;
    for (int x = std::max(0, line - 1); x < std::min(board_size, line + 2); x++){
        for (int y = std::max(0, col - 1); y < std::min(board_size, col + 2); y++){
            if (!board[x][y].show and board[x][y].info == BOMB and (x != line or y != col)){ // The AI knows there is a bomb in this tile
                bombs++;
            }
            if (!board[x][y].show and board[x][y].info == MAYBE and (x != line or y != col)){
                ans.push_back({x, y});
            }
        }
    }
    num_bombs -= bombs;
    return ans;
}

Game_State Minesweeper::game_state() const{
    int num_played_tiles = 0, num_bombs = 0;
    for (int x = 0; x < board_size; x++){
        for (int y = 0; y < board_size; y++){
            if (board[x][y].show and board[x][y].num == -1){ // AI choose a Tile with a bomb
                return LOST;
            }
            else if (board[x][y].show){
                num_played_tiles++;
            }
            else if (board[x][y].num == -1){
                num_bombs++;
            }
        }
    }
    return (num_played_tiles == board_size * board_size - num_bombs ? WON : PLAYING);
}

int Minesweeper::num_close_bombs(int line, int col){
    int num_bombs = 0;
    for (int x = std::max(0, line - 1); x < std::min(board_size, line + 2); x++){
        for (int y = std::max(0, col - 1); y < std::min(board_size, col + 2); y++){
            if (board[x][y].num == -1){ // It is a bomb
                num_bombs++;
            }
        }
    }
    return num_bombs;
}

void Minesweeper::update_tile_info(){
    for (int x = 0; x < board_size; x++){
        for (int y = 0; y < board_size; y++){
            // Only counts the close bombs if the current tile is not a bomb itself, because makes no sense to count has the AI will lose if it chooses it
            if (board[x][y].num != -1){
                board[x][y].num = num_close_bombs(x, y);
            }
        }
    }
}

void Minesweeper::update_close_tiles_info(int line, int col){
    mark_close_tiles_maybe(line, col);
}

bool Minesweeper::play(const Coordinates& coor){
    if (board[coor.x][coor.y].show){
        return false;
    }
    board[coor.x][coor.y].show = true;
    return true;
}

void Minesweeper::mark_close_tiles_safe(int line, int col){
    for (int x = std::max(0, line - 1); x < std::min(board_size, line + 2); x++){
        for (int y = std::max(0, col - 1); y < std::min(board_size, col + 2); y++){
            if (!board[x][y].show and (x != line or y != col) and board[x][y].info != BOMB){
                board[x][y].info = NO_BOMB;
            }
        }
    }
}

void Minesweeper::mark_close_tiles_maybe(int line, int col){
    for (int x = std::max(0, line - 1); x < std::min(board_size, line + 2); x++){
        for (int y = std::max(0, col - 1); y < std::min(board_size, col + 2); y++){
            if (!board[x][y].show and (x != line or y != col) and board[x][y].info == NO_CLUE){ // board[x][y].info == NO_CLUE guarantees that the AI does not override a tile it knows for sure is a bomb or safe
                board[x][y].info = MAYBE;
            }
        }
    }
}

void Minesweeper::show_board() const{
    #ifdef _WIN32    
        system("cls");
    #else
        //system("clear");
    #endif
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            std::cout << "+---";
        }
        std::cout << "+\n";

        // Draw the sides and space within the cells
        for (int j = 0; j < board_size; j++) {
            std::cout << "| ";
            if (!board[i][j].show){
                if (board[i][j].info == BOMB){ // The AI didn't choose this tile but knows is a bomb
                    std::cout << "\033[32mX\033[0m";
                } 
                else if (board[i][j].info == NO_BOMB) {
                    std::cout << "\033[34mS\033[0m";
                } else {
                    std::cout << " ";
                }
            }
            else if (board[i][j].num == -1){ // It is a bomb, meaning the AI lost because it choose a bomb
                std::cout << "\033[31mX\033[0m";
            }
            else{
                std::cout << (char)('0' + board[i][j].num);
            }
            std::cout << " ";
        }
        std::cout << "|\n";
    }

    // Draw the bottom border of the last row
    for (int j = 0; j < board_size; j++) {
        std::cout << "+---";
    }
    std::cout << "+\n";
}