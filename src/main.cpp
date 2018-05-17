#include <iostream>
#include "Game.h"

#include <fstream>
#include <TitleState.h>

int main(int argc, char **argv) {
    Game::GetInstance().Push(new TitleState);
    Game::GetInstance().Run();

    return 0;
}