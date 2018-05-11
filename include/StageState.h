//
// Created by bruno on 18/03/18.
//



#ifndef INC_140017658_T1_STATE_H
#define INC_140017658_T1_STATE_H

#define INCLUDE_SDL
#include <memory>
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "State.h"

class StageState : public State {
public:
    StageState();
    ~StageState();

    void LoadAssets() override;
    void Update (float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:

    TileSet* tileSet;
    Music backgroundMusic;
};


#endif //INC_140017658_T1_STATE_H
