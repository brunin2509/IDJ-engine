#include <iostream>
#include "Game.h"

#include <fstream>

int main(int argc, char **argv) {
    Game::GetInstance().Run();

//    std::ifstream file;
//    std::string line;
//
//    file.open("./assets/map/tileMap.txt");
//
//    if(file.is_open()){
//        std::string str;
//        int index = 0;
//        char comma = 0;
//
//        file >> str;
//
//        for(int i = 0; i < 25*25*2; i++){
//            file >> index;
//            file >> comma;
//            std::cout << index << comma << "\n";
//        }
//
//    }
//    else{
//        std::cout << "File could not be open\n";
//    }
//
//    file.close();

    return 0;
}