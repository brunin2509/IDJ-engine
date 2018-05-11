#include <iostream>
#include "Game.h"

#include <fstream>

int main(int argc, char **argv) {
    Game::GetInstance().Push(new StageState);
    Game::GetInstance().Run();

    return 0;
}