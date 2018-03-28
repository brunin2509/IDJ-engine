//
// Created by bruno on 18/03/18.
//

#include <Sound.h>
#include "State.h"

State::State() : bg("./assets/img/ocean.jpg"), music("./assets/audio/stageState.ogg") {
    quitRequested = false;
    music.Play();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    Input(); //todo

    for (auto &gameObjects : objectArray) {
        gameObjects->Update(dt);
    }

    for (int i = 0; i < objectArray.size(); i++) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
    }

    quitRequested = SDL_QuitRequested(); //todo: tira ou nao?
}

void State::Render() {
    for (auto &gameObjects : objectArray) {
        gameObjects->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Input() {
    //todo: corpo desse metodo no moodle
}

void State::AddObject(int mouseX, int mouseY) {
    auto gameObject = new GameObject();

    auto sprite = new Sprite(*gameObject, "./assets/img/penguin.jpg");

    gameObject->box.x = mouseX - gameObject->box.w/2;
    gameObject->box.y = mouseY - gameObject->box.h/2;

    auto sound = new Sound(*gameObject, "./assets/audio/boom.wav");

    //todo
}



