#include <iostream>
#include <fstream>
#include "../header/Game.hpp"

int main() {
    while (true){
        std::cout << "Enter the file name: ";
        std::string file_path;
        file_path = "assets/board1.minesweeper";
        //std::cin >> file_path;
        std::ifstream in(file_path);
        if (!in.is_open()){
            std::cout << "Invalid path.\n";
            continue;
        }
        Game game(in);
        game.run();
        std::cout << "Wanna leave? [y/n]: ";
        std::string ans;
        std::cin >> ans;
        if (ans == "y") break;
    }
    return 0;
}
