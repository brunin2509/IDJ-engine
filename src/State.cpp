//
// Created by bruno on 18/03/18.
//

#include <Sound.h>
#include <Face.h>
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
    bgGO->box.x = 0;
    bgGO->box.y = 0;

    auto bg = new Sprite(*bgGO, "./assets/img/ocean.jpg");
    auto bgCamFollower = new CameraFollower(*bgGO);

    bgGO->AddComponent(bg);
    bgGO->AddComponent(bgCamFollower);

    objectArray.emplace_back(bgGO);


    // carrega variaveis relativas ao mapa
    auto mapGO = new GameObject();
    mapGO->box.x = 0;
    mapGO->box.y = 0;

    auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
    auto tileMap = new TileMap(*mapGO, ".assets/map/tileMap.txt", tileSet);

    mapGO->AddComponent(tileMap);

    // Remember: o mapGO eh o SEGUNDO objeto no objectArray (indice 1)
    objectArray.emplace_back(mapGO);


    // carrega um alien
    auto alienGO = new GameObject();

    auto alien = new Alien(*alienGO, 3);
    alienGO->box.x = 512;
    alienGO->box.y = 300;
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

    // se apertar espaco, cria um Face
    if( inputManager.KeyPress(SPACE_KEY) ) {
        Vec2 objPos = Vec2(200, 0).Rotate((float)(-PI + PI * (std::rand() % 1001) / 500.0)) +
                      Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());

        AddObject((int)objPos.x, (int)objPos.y);
    }

    // executa o update em cada um dos objetos no objectArray
    for (auto &gameObjects : objectArray) {
        gameObjects->Update(dt);
    }

    // depois de executar os updates, verifica se algum deles morreu
    for (int i = 0; i < objectArray.size(); i++) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
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

void State::AddObject(int mouseX, int mouseY) {
    auto gameObject = new GameObject();

    auto sprite = new Sprite(*gameObject, "./assets/img/penguinface.png");

    gameObject->box.x = mouseX + Camera::pos.x;
    gameObject->box.y = mouseY + Camera::pos.y;
    gameObject->box.Centralize();

    auto sound = new Sound(*gameObject, "./assets/audio/boom.wav");

    auto face = new Face(*gameObject);

    gameObject->AddComponent(sprite);
    gameObject->AddComponent(sound);
    gameObject->AddComponent(face);

    objectArray.emplace_back(gameObject);
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



