#include <iostream>
#include "Game.h"

#include <fstream>

int main(int argc, char **argv) {
    Game::GetInstance().Run();

//    bool array[6];
//
//    memset(array, true, sizeof(array));
//
//    for(auto a : array){
//        std::cout << std::to_string(a) << "\n";
//    }

    return 0;
}