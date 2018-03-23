//
// Created by bruno on 18/03/18.
//



#ifndef INC_140017658_T1_STATE_H
#define INC_140017658_T1_STATE_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"

class State {
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update (float dt);
    void Render();

private:
    Sprite bg;
    Music music;
    bool quitRequested;
};


#endif //INC_140017658_T1_STATE_H
