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

bool Minesweeper::play(const Coordinates& coor){
    if (board[coor.x][coor.y].show){
        return false;
    }
    board[coor.x][coor.y].show = true;
    return true;
}

Coordinates Minesweeper::get_close_tile_not_played(int line, int col) const{
    for (int x = std::max(0, line - 1); x < std::min(board_size, line + 2); x++){
        for (int y = std::max(0, col - 1); y < std::min(board_size, col + 2); y++){
            if (!board[x][y].show and (x != line or y != col)){
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

void Minesweeper::show_board() const{
    #ifdef _WIN32    
        system("cls");
    #else
        system("clear");
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
                std::cout << " ";
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