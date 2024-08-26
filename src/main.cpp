#include <iostream>
#include <fstream>
#include "../header/Game.hpp"

int main() {
    while (true){
        std::cout << "Do you want ro see the knowledge at each state? [y/n]: ";
        std::string ans;
        std::cin >> ans;
        bool show = (ans == "y" ? true : false);

        std::cout << "Enter the file name: ";
        std::string file_path;
        std::cin >> file_path;
        std::ifstream in(file_path);
        if (!in.is_open()){
            std::cout << "Invalid path.\n";
            continue;
        }
        Game game(in, show);
        game.run();
        std::cout << "Wanna leave? [y/n]: ";
        std::cin >> ans;
        if (ans == "y") break;
    }
    return 0;
}
