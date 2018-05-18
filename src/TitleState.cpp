//
// Created by bruno on 11/05/18.
//

#include <CameraFollower.h>
#include <Sprite.h>
#include <InputManager.h>
#include <StageState.h>
#include <Game.h>
#include <Text.h>
#include <Camera.h>
#include "TitleState.h"

TitleState::TitleState(): State() {
    // criacao da imagem de titulo
    auto bgGO = new GameObject();
    bgGO->box = {0,0};
    auto bg = new Sprite(*bgGO, "./assets/img/title.jpg");
    bgGO->AddComponent(bg);
    objectArray.emplace_back(bgGO);

    // criacao do texto de "press to play"
    auto textGO = new GameObject();
    auto textColor = Text::GetSDLColor(255, 150, 0, 255);
    auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 60, Text::SOLID, "Press SPACE to play!", textColor, 0.7);
    textGO->AddComponent(text);
    textGO->box.PlaceCenterAt({Game::GetInstance().GetWidth()/2.0f, Game::GetInstance().GetHeight()/2.0f});
    objectArray.emplace_back(textGO);
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
    Camera::pos = {0,0};
}