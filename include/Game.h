//
// Created by bruno on 16/03/18.
//

#ifndef T1_PROJECT_GAME_H
#define T1_PROJECT_GAME_H

#define INCLUDE_SDL

#include <stack>
#include "SDL_include.h"
#include "StageState.h"
#include "State.h"

class Game {
public:
    ~Game();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();

    void Push(State* state);

    void Run();

    float GetDeltaTime();

    int GetWidth();
    int GetHeight();

private:
    Game(std::string title, int width, int height);

    void CalculateDeltaTime();

    int frameStart;
    float dt;

    static Game* instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::stack<std::unique_ptr<State>> stateStack;

    int width;
    int height;

};

#endif //T1_PROJECT_GAME_H

