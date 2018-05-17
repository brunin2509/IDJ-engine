//
// Created by bruno on 11/05/18.
//

#include <CameraFollower.h>
#include <Sprite.h>
#include <InputManager.h>
#include <StageState.h>
#include <Game.h>
#include "TitleState.h"

TitleState::TitleState(): State() {
    //
    auto bgGO = new GameObject();
    bgGO->box = {0,0};

    auto bg = new Sprite(*bgGO, "./assets/img/title.jpg");
    auto bgCamFollower = new CameraFollower(*bgGO);

    bgGO->AddComponent(bg);
    bgGO->AddComponent(bgCamFollower);

    objectArray.emplace_back(bgGO);
}

TitleState::~TitleState() {
    objectArray.clear();
}

void TitleState::LoadAssets() {
}

void TitleState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    // se apertar esc, seta o quitRequested
    quitRequested =  inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

    if(inputManager.KeyPress(SPACE_KEY)){
        Game::GetInstance().Push(new StageState);
    }

    // executa o update em cada um dos objetos no objectArray
    UpdateArray(dt);
}

void TitleState::Render() {
    // executa o render em cada um dos objetos no objectArray
    RenderArray();
}

void TitleState::Start() {
    LoadAssets();

    // executa o start em cada um dos objetos no objectArray
    StartArray();
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}