//
// Created by bruno on 18/03/18.
//

#include <Sound.h>
#include <TileSet.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include "State.h"
#include "TileMap.h"

State::State(): music("./assets/audio/stageState.ogg"), quitRequested(false), started(false) {
    music.Play();

    // carrega variaveis relativas ao background
    auto bgGO = new GameObject();
    bgGO->box = {0,0};

    auto bg = new Sprite(*bgGO, "./assets/img/ocean.jpg");
    auto bgCamFollower = new CameraFollower(*bgGO);

    bgGO->AddComponent(bg);
    bgGO->AddComponent(bgCamFollower);

    objectArray.emplace_back(bgGO);


    // carrega variaveis relativas ao mapa
    auto mapGO = new GameObject();
    mapGO->box = {0,0};

    auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
    auto tileMap = new TileMap(*mapGO, ".assets/map/tileMap.txt", tileSet);

    mapGO->AddComponent(tileMap);

    // Remember: o mapGO eh o SEGUNDO objeto no objectArray (indice 1)
    objectArray.emplace_back(mapGO);


    // carrega um alien
    auto alienGO = new GameObject();

    auto alien = new Alien(*alienGO, 3);
    alienGO->box = {512,300};
    alienGO->box.Centralize();

    alienGO->AddComponent(alien);

    objectArray.emplace_back(alienGO);
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    // atualiza a camera e a box do GameObject do mapa (lembrando novamente que o GO do mapa esta no indice 1)
    Camera::Update(dt);

    // se apertar esc, seta o quitRequested
    quitRequested =  inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

    // executa o update em cada um dos objetos no objectArray
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    // depois de executar os updates, verifica se algum deles morreu
    for (unsigned i = 0; i < objectArray.size(); i++) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render() {
    for (auto &gameObjects : objectArray) {
        gameObjects->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Start() {
    LoadAssets();

    for (auto &gameObjects : objectArray) {
        gameObjects->Start();
    }

    started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
    std::shared_ptr<GameObject> sharedGO(go);

    objectArray.push_back(sharedGO);

    if(started){
        go->Start();
    }
    return std::weak_ptr<GameObject>(sharedGO);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
    for(auto& it : objectArray){
        if(it.get() == go){
            return std::weak_ptr<GameObject>(it);
        }
    }

    return std::weak_ptr<GameObject>();
}



