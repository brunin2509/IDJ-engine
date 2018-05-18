//
// Created by bruno on 21/04/18.
//

#include <Sprite.h>
#include <Game.h>
#include <InputManager.h>
#include <Collider.h>
#include <Bullet.h>
#include <Camera.h>
#include <Sound.h>
#include "PenguinBody.h"
#include "PenguinCannon.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) :
        Component(associated),
        pcannon(),
        speed(1,0),
        linearSpeed(0),
        angle(0),
        hp(PENGUIN_INITIAL_HP){

    player = this;

    auto sprite = new Sprite(associated, "./assets/img/penguin.png");
    associated.AddComponent(sprite);
    associated.AddComponent(new Collider(associated));
    associated.angleDeg = angle * 180/PI;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    auto cannonGO = new GameObject();
    auto cannon = new PenguinCannon(*cannonGO, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
    cannonGO->AddComponent(cannon);

    pcannon = Game::GetInstance().GetCurrentState().AddObject(cannonGO);
}

void PenguinBody::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    double angleVariation = 0;

    if(hp <= 0){
        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
        Camera::Unfollow();

        auto explosionGO = new GameObject();
        auto explosionSound = new Sound(*explosionGO, "./assets/audio/boom.wav");
        explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/penguindeath.png", 5, 0.1, 0.5));
        explosionGO->AddComponent(explosionSound);
        explosionSound->Play();
        explosionGO->box.PlaceCenterAt(associated.box.Center());
        Game::GetInstance().GetCurrentState().AddObject(explosionGO);

        return;
    }

    double accelSpeedGain = PENGUIN_ACCELERATION*dt;

    if(inputManager.IsKeyDown(W_KEY) && (PENGUIN_MAX_LINEAR_SPEED-abs(linearSpeed) > accelSpeedGain)){
        linearSpeed += accelSpeedGain;
    }
    else if(inputManager.IsKeyDown(S_KEY) && (PENGUIN_MAX_LINEAR_SPEED-abs(linearSpeed) > accelSpeedGain)){
        linearSpeed -= accelSpeedGain;
    }

    if(inputManager.IsKeyDown(A_KEY)){
        angleVariation = PENGUIN_ANGULAR_SPEED*dt;
        angle -= angleVariation;
        associated.angleDeg = angle * 180/PI;
        speed = speed.Rotate(-angleVariation);
    }
    else if(inputManager.IsKeyDown(D_KEY)){
        angleVariation = PENGUIN_ANGULAR_SPEED*dt;
        angle += angleVariation;
        associated.angleDeg = angle * 180/PI;
        speed = speed.Rotate(angleVariation);
    }

    double atrictSpeedLoss = PENGUIN_ATRICT*dt;

    if(abs(linearSpeed) > atrictSpeedLoss){
        linearSpeed -= (linearSpeed < 0)? -1*atrictSpeedLoss : atrictSpeedLoss;
        Rect newPos = associated.box + speed*linearSpeed*dt;

        if(newPos.Center().x > PENGUIN_WALKING_LIMIT_X_MIN && newPos.Center().x < PENGUIN_WALKING_LIMIT_X_MAX
                && newPos.Center().y > PENGUIN_WALKING_LIMIT_Y_MIN && newPos.Center().y < PENGUIN_WALKING_LIMIT_Y_MAX){
            associated.box = newPos;
        }
    }
    else{
        linearSpeed = 0;
    }
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
    return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject &other) {
    auto bullet = (Bullet*) other.GetComponent("Bullet");
    if(bullet && bullet->targetsPlayer){
        hp -= bullet->GetDamage();
    }
}

Vec2 PenguinBody::GetCenter() {
    return associated.box.Center();
}

