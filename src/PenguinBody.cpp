//
// Created by bruno on 21/04/18.
//

#include <Sprite.h>
#include <Game.h>
#include <InputManager.h>
#include "PenguinBody.h"
#include "PenguinCannon.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) :
        Component(associated),
        pcannon(),
        speed(1,0),
        linearSpeed(0),
        angle(0),
        hp(100){

    player = this;

    auto sprite = new Sprite(associated, "penguin.png");
    associated.AddComponent(sprite);
    associated.angleDeg = angle * 180/PI;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    auto cannonGO = new GameObject();
    auto cannon = new PenguinCannon(*cannonGO, Game::GetInstance().GetState().GetObjectPtr(&associated));
    cannonGO->AddComponent(cannon);

    pcannon = Game::GetInstance().GetState().AddObject(cannonGO);
}

void PenguinBody::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    double angleVariation = 0;

    if(hp <= 0){
        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
        return;
    }

    if(inputManager.IsKeyDown(W_KEY)){
        linearSpeed += PENGUIN_ACCELERATION*dt;
    }
    else if(inputManager.IsKeyDown(S_KEY)){
        linearSpeed -= PENGUIN_ACCELERATION*dt;
    }

    if(inputManager.IsKeyDown(A_KEY)){
        angleVariation = PENGUIN_ANGULAR_SPEED*dt;
        angle += angleVariation;
        associated.angleDeg = angle * 180/PI;
        speed = speed.Rotate(angleVariation);
    }
    else if(inputManager.IsKeyDown(D_KEY)){
        angleVariation = PENGUIN_ANGULAR_SPEED*dt;
        angle -= angleVariation;
        associated.angleDeg = angle * 180/PI;
        speed = speed.Rotate(-angleVariation);
    }

    if(linearSpeed != 0){
        linearSpeed -= PENGUIN_ATRICT*dt;
        associated.box += speed*linearSpeed;
    }
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
    return type == "PenguinBody";
}

