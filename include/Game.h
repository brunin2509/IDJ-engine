//
// Created by bruno on 16/03/18.
//

#ifndef T1_PROJECT_GAME_H
#define T1_PROJECT_GAME_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include "StageState.h"

class Game {
public:
    ~Game();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    StageState& GetState();

    void Run( );
    
    float GetDeltaTime();

    int GetWidth();
    int GetHeight();

private:
    Game(std::string title, int width, int height);

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    StageState* state;

    int frameStart;
    float dt;
    int width;
    int height;

    void CalculateDeltaTime();
};

#endif //T1_PROJECT_GAME_H

