//
// Created by bruno on 16/03/18.
//

#ifndef T1_PROJECT_GAME_H
#define T1_PROJECT_GAME_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

class Game {
public:
    ~Game();
    void Run( );
    float GetDeltaTime();

    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();

private:
    Game(std::string title, int width, int height);

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    int frameStart;
    float dt;

    void CalculateDeltaTime();
};

#endif //T1_PROJECT_GAME_H

