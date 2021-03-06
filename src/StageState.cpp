//
// Created by bruno on 18/03/18.
//

#include <Sound.h>
#include <TileSet.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include <PenguinBody.h>
#include <Collider.h>
#include <Collision.h>
#include <Game.h>
#include <EndState.h>
#include <GameData.h>
#include "StageState.h"
#include "TileMap.h"

StageState::StageState(): State(), backgroundMusic("./assets/audio/stageState.ogg") {
    backgroundMusic.Play();

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
    for(int i = 0; i < NUM_OF_ALIENS; i++){
        auto alienGO = new GameObject();

        auto alien = new Alien(*alienGO, 3, (std::rand() % (ALIEN_RESTING_TIME*100))/100.f);

        alienGO->AddComponent(alien);
        alienGO->box.PlaceCenterAt({float(std::rand() % 1408),float(std::rand() % 1280)});

        objectArray.emplace_back(alienGO);
    }


    // carrega o penguin
    auto penguinGO = new GameObject();

    auto penguin = new PenguinBody(*penguinGO);
    penguinGO->AddComponent(penguin);
    penguinGO->box.PlaceCenterAt(Vec2(704,640));

    objectArray.emplace_back(penguinGO);

    Camera::Follow(penguinGO);
}

StageState::~StageState() {
    objectArray.clear();
}

void StageState::LoadAssets() {
}

void StageState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    // atualiza a camera e a box do GameObject do mapa (lembrando novamente que o GO do mapa esta no indice 1)
    Camera::Update(dt);

    // se fechar o jogo, seta o quitRequested
    quitRequested =  inputManager.QuitRequested();

    // se apertar esc, seta o popRequested
    popRequested =  inputManager.KeyPress(ESCAPE_KEY);

    // executa o update em cada um dos objetos no objectArray
    UpdateArray(dt);

    // Collider* colliders[objectArray.size()];
    std::vector<Collider*> colliders(objectArray.size(), nullptr);
    bool collidersArrayFilled = false;

    // verifica colisoes entre os objetos que sao Colliders
    for (unsigned i = 0; i < objectArray.size()-1; i++) {
        if(!collidersArrayFilled){
            colliders[i] = (Collider*)objectArray[i]->GetComponent("Collider");
        }

        if(colliders[i]) {
            for (unsigned j = i+1; j < objectArray.size(); j++) {
                if(!collidersArrayFilled){
                    colliders[j] = (Collider*)objectArray[j]->GetComponent("Collider");
                }
                if(colliders[j] && Collision::IsColliding(colliders[i]->box, colliders[j]->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg)){
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
            }
            collidersArrayFilled = true;
        }
    }

    // depois de executar os updates, verifica se algum deles morreu
    for (unsigned i = 0; i < objectArray.size(); i++) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }

    if(!PenguinBody::player){
        GameData::playerVictory = false;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }
    else if(Alien::alienCount == 0){
        GameData::playerVictory = true;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }
}

void StageState::Render() {
    // executa o render em cada um dos objetos no objectArray
    RenderArray();
}

void StageState::Start() {
    LoadAssets();

    // executa o start em cada um dos objetos no objectArray
    StartArray();
}

void StageState::Pause() {

}

void StageState::Resume() {

}



