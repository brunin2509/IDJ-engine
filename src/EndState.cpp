//
// Created by bruno on 18/05/18.
//

#include <GameData.h>
#include <Sprite.h>
#include <Text.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include "EndState.h"

EndState::EndState() : State() {
    auto bgGO = new GameObject();
    bgGO->box = {0,0};
    Sprite* bg = nullptr;

    if(GameData::playerVictory){
        backgroundMusic = Music("./assets/audio/endStateWin.ogg");
        backgroundMusic.Play();

        bg = new Sprite(*bgGO, "./assets/img/win.jpg");
    }
    else{
        backgroundMusic = Music("./assets/audio/endStateLose.ogg");
        backgroundMusic.Play();

        bg = new Sprite(*bgGO, "./assets/img/lose.jpg");
    }

    bgGO->AddComponent(bg);
    objectArray.emplace_back(bgGO);

    // criacao do texto de "press to play"
    auto textGO = new GameObject();
    auto textColor = Text::GetSDLColor(255, 150, 0, 255);
    auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 40, Text::SOLID, "Press SPACE to play again, or ESC to exit", textColor, 0.7);
    textGO->AddComponent(text);
    textGO->box.PlaceCenterAt({Game::GetInstance().GetWidth()/2.0f, Game::GetInstance().GetHeight()/2.0f});
    objectArray.emplace_back(textGO);
}

EndState::~EndState() {
    objectArray.clear();
}

void EndState::LoadAssets() {

}

void EndState::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();

    // se apertar esc, seta o quitRequested
    quitRequested =  inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

    if(inputManager.KeyPress(SPACE_KEY)){
        popRequested = true;
    }

    // executa o update em cada um dos objetos no objectArray
    UpdateArray(dt);
}

void EndState::Render() {
    // executa o render em cada um dos objetos no objectArray
    RenderArray();
}

void EndState::Start() {
    LoadAssets();

    Camera::pos = {0,0};

    // executa o start em cada um dos objetos no objectArray
    StartArray();
}

void EndState::Pause() {

}

void EndState::Resume() {

}
